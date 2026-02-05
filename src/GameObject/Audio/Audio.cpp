#include "Audio.h"

Audio::Audio(int _soundHandle, bool _is3D)
	:GameObject()
	, is3DSound(_is3D)
	, isLoop(false)
	, soundHandle(_soundHandle)
	, volume(255)
	, distance(800.0f)
{
	Start();
}

Audio::~Audio()
{
	DeleteSoundMem(soundHandle);
}



void Audio::Start()
{
	// 音量の設定
	ChangeVolumeSoundMem((int)volume, soundHandle);

	if (isLoop) {
		PlaySoundMem(soundHandle, DX_PLAYTYPE_LOOP);
	}
	else {
		PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
	}
}

void Audio::Update()
{
	if (!isVisible) {
		return;
	}

	// 再生中かどうか
	if (CheckSoundMem(soundHandle) == 0) {
		isVisible = false;
	}

	// 音量の設定
	ChangeVolumeSoundMem((int)volume, soundHandle);

	// 3Dサウンドの設定
	if (is3DSound) {
		// 音源の位置の設定
		Set3DPositionSoundMem(position, soundHandle);
		// 音が聞こえる範囲の設定
		Set3DRadiusSoundMem(distance, soundHandle);
	}
}

void Audio::Render()
{
}
