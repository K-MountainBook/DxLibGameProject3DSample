#include "FadeManager.h"
#include "TimeManager.h"

FadeManager* FadeManager::pInstance = nullptr;

FadeManager::FadeManager()
	:blend(0.0f)
	, time(0.0f)
	, fadeState(FadeState::FadeEnd)
{
}

FadeManager::~FadeManager() {

}

void FadeManager::CreateInstance()
{
	pInstance = new FadeManager();
}

FadeManager* FadeManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}
	return pInstance;
}

void FadeManager::DestroyInstance()
{
}

void FadeManager::Update()
{
	// フェード処理が完了していたら更新しない
	if (fadeState == FadeState::FadeEnd) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		return;
	}

	blend += 255 * (int)fadeState * TimeManager::GetInstance()->GetDeltaTime() / time;

	if (blend <= 0) {
		blend = 0;
		fadeState = FadeState::FadeEnd;
	}

	if (blend >= 255) {
		blend = 0;
		fadeState = FadeState::FadeEnd;
	}

	//switch (fadeState)
	//{
	//case FadeState::FadeIn:
	//	// フェードイン
	//	// n秒で255から0へ
	//	blend -= 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
	//	break;
	//case FadeState::FadeOut:
	//	// フェードアウト
	//	// n秒で0から255へ
	//	blend += 255 * TimeManager::GetInstance()->GetDeltaTime() / time;
	//	break;
	//default:
	//	break;
	//}

}

void FadeManager::Render()
{
	// フェード処理が完了していたら描画しない
	if (fadeState == FadeState::FadeEnd) {
		return;
	}

	// 透明度を変化させてフェード処理を行う
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)blend);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, black, true);
	// ブレンド状態を戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void FadeManager::FadeIn(float _t)
{
	fadeState = FadeState::FadeIn;
	time = _t;
	blend = 255.0f;
}

void FadeManager::FadeOut(float _t)
{
	fadeState = FadeState::FadeOut;
	time = _t;
	blend = 0.0f;
}

