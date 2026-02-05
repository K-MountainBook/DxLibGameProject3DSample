#include "AudioManager.h"
#include "../GameObject/Audio/Audio.h"


AudioManager* AudioManager::pInstance = nullptr;

AudioManager::AudioManager()
	:audioResourceMap()
	, pAudioList()
{
}

AudioManager::~AudioManager()
{
	for (auto audio : audioResourceMap) {
		DeleteSoundMem(audio.second);
	}

	for (auto pA : pAudioList) {
		if (pA != nullptr) {
			delete pA;
			pA = nullptr;
		}
	}

	pAudioList.clear();
}

void AudioManager::CreateInstance()
{
	pInstance = new AudioManager();
}

AudioManager* AudioManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}
	return pInstance;
}

void AudioManager::DestroyInstance()
{
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

void AudioManager::Load(std::string _filePath, std::string _name, bool _is3D)
{
	// 読み込み
	SetCreate3DSoundFlag(_is3D);
	int res = LoadSoundMem(_filePath.c_str());

	// 連想配列の中にすでに登録されているファイルか検索する。
	auto itr = audioResourceMap.find(_name.c_str());
	// 登録されていなければ登録する
	// マップが最後まで来ているということは検索しても無かった
	if (itr == audioResourceMap.end()) {
		// 登録
		audioResourceMap.emplace(_name.c_str(), res);
	}

}

void AudioManager::ChangeVolume(std::string _name, float _volume)
{
	if (_name == "All") {
		// 全ての音量の変更
		for (auto pA : pAudioList) {
			pA->setVolume(_volume);
		}
	}
	else {
		for (auto pA : pAudioList)
			if (pA->GetTag() == _name) {
				pA->setVolume(_volume);
			}
	}

}

void AudioManager::PlayOneShot(std::string _name, float _volume)
{
	// 3分未満のみ利用可能
	Audio* pAudioObj = new Audio(DuplicateSoundMem(audioResourceMap[_name]));
	pAudioObj->SetTag(_name);
	pAudioObj->Start();
	pAudioList.push_back(pAudioObj);
}

void AudioManager::PlayClipAtPoint(std::string _name, VECTOR _pos, float _volume, bool _loop)
{
	// 3分未満のみ利用可能
	// getsoundtotaltimeを使うことで音声の再生時間を取得することができる
	int sound = INVALID;
	if (GetSoundTotalTime(audioResourceMap[_name]) >= 1000 * 60 * 3) {
		sound = audioResourceMap[_name];
	}
	else {
		sound = DuplicateSoundMem(audioResourceMap[_name]);
	}

	Audio* pAudioObj = new Audio(audioResourceMap[_name]);
	pAudioObj->SetTag(_name);
	pAudioObj->SetPosition(_pos);
	pAudioObj->setIsLoop(_loop);
	pAudioObj->Start();
	pAudioList.push_back(pAudioObj);
}

void AudioManager::Stop(std::string _name)
{
	if (_name == "All") {
		// 全ての音量の変更
		for (auto pA : pAudioList) {
			StopSoundMem(pA->GetSoundHandle());
		}
	}
	else {
		for (auto pA : pAudioList)
			if (pA->GetTag() == _name) {
				StopSoundMem(pA->GetSoundHandle());
			}
	}
}

void AudioManager::Update()
{
	for (auto pA : pAudioList) {
		if (pA == nullptr || !pA->IsVisible()) {
			continue;
		}
		pA->Update();
	}

	std::erase_if(
		pAudioList,
		[](Audio* _pA) {		return !_pA->IsVisible();	}
	);

}
