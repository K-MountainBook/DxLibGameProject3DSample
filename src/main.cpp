#include <iostream>
#include <DxLib.h>
#include "Definition.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"
#include "Component/DebugDisplay.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// int key;
	// プレイヤーの位置
	VECTOR pos = VGet(0.0f, 280.0f, -400.0f);
	// カメラポジション
	VECTOR cpos = VGet(0.0f, 180.0f, -400.0f);
	// 注視点
	VECTOR ctgt = VGet(0.0f, 0.0f, 400.0f);
	bool running = false;

	SetGraphMode(WINDOW_WIDTH_HD, WINDOW_HEIGHT_HD, 32, FPS_60);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// フレームレート調整用カウンタ（ミリ秒
	LONGLONG frameRateAdjCounter = 0;
	LONGLONG prevFrameTime = 0;
	float fps = 0.0f;

	// 書き込み先をバックバッファに設定
	SetDrawScreen(DX_SCREEN_BACK);

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

	// デバッグにインプットマネージャーとシーンマネージャーをセット
	DebugDisplay::GetInstance()->SetInputManager(InputManager::GetInstance());
	DebugDisplay::GetInstance()->SetSceneManager(SceneManager::GetInstance());

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		// メインループの開始時間を取得する
		frameRateAdjCounter = GetNowHiPerformanceCount();

		// update
		InputManager::GetInstance()->Update();
		SceneManager::GetInstance()->Update();

		ClearDrawScreen();

		SceneManager::GetInstance()->Render();

#if _DEBUG
		DebugDisplay::GetInstance()->Render();
#endif

		// 前フレームからの経過時間を取得する
		LONGLONG deltaTime = (frameRateAdjCounter - prevFrameTime);

		DrawFormatString(0, 700, red, L"FPS:%.2f", ((float)1.0f / (float)deltaTime) * 1000000.0f);

		// スクリーンバッファの入れ替え
		ScreenFlip();

		// フレームレート調整
		while (true) {
			if (GetNowHiPerformanceCount() - frameRateAdjCounter >= 1000.0f * 1000.0f / FPS_60) {
				break;
			}
		}

		// メインループの開始時間を退避
		prevFrameTime = frameRateAdjCounter;
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}