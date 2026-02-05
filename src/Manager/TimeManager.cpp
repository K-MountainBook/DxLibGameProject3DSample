#include "TimeManager.h"
#include <DxLib.h>
#include "../Definition.h"

#pragma region "singleton data structure"
TimeManager* TimeManager::pInstance = nullptr;

// コンストラクタ
TimeManager::TimeManager()
	:prevTime(GetNowCount())
	, currentTime(prevTime)
	, deltaTime(currentTime - prevTime)
	, m(0)
	, s(0)
	, ms(0)
{
	Start();
}

TimeManager::~TimeManager()
{

}
#pragma region
/// <summary>
/// インスタンスの生成
/// </summary>
void TimeManager::CreateInstance()
{
	pInstance = new TimeManager();
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
TimeManager* TimeManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}

	return pInstance;
}

/// <summary>
/// インスタンスの破棄
/// </summary>
void TimeManager::DestroyInstance()
{
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

#pragma endregion

void TimeManager::Start()
{
}

void TimeManager::Update()
{
	// 今のフレーム時間を取得
	currentTime = GetNowCount();

	if (!GetNoActiveState()) {

		// 1フレーム前の時間との差分を計算する
		deltaTime = currentTime - prevTime;

		// 時間の計算を行う
		ms += deltaTime;
		if (ms >= 1000) {
			ms = 0;
			s++;
		}
		if (s >= 60) {
			s = 0;
			m++;
		}


		//deltaTimeをunityのごとく使うために単位を秒に変換する。
		deltaTime /= 1000.0f;
	}
	// 1フレーム前の時間を現在の時間で置き換える
	prevTime = currentTime;
}

void TimeManager::Render()
{
	DrawFormatString(500, 0, red, "%02d:%02d:%03d", m, s, ms);
	DrawFormatString(500, 20, red, "FPS:%0.0f", 1.0f / deltaTime);

}
