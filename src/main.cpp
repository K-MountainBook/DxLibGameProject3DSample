#include <iostream>
#include <DxLib.h>
#include "Definition.h"
#include "Manager/SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int key;
	// プレイヤーの位置
	VECTOR pos = VGet(0.0f, 280.0f, -400.0f);
	// カメラポジション
	VECTOR cpos = VGet(0.0f, 480.0f, -800.0f);
	// 注視点
	VECTOR ctgt = VGet(0.0f, 280.0f, -400.0f);
	bool running = false;

	XINPUT_STATE xinput;
	int inputX, inputY;

	MATRIX mat1, mat2;

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

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		frameRateAdjCounter = GetNowHiPerformanceCount();

		// update
		SceneManager::
		
		key = 0;
		//key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
		GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

		ClearDrawScreen();
		// メイン処理を記載
		// 背景の描画
		DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
		



		// mat1 = MGetRotY(DX_PI / 2 * direction);
		// mat2 = MGetTranslate(pos);
		// MV1SetMatrix(model1, MMult(mat1, mat2));

		// 前フレームからの経過時間を取得する
		int deltaTime = (frameRateAdjCounter - prevFrameTime);

		DrawFormatString(0, 0, red, L"FPS:%.2f", ((float)1.0f / (float)deltaTime) * 1000000.0f);

		// スクリーンバッファの入れ替え
		ScreenFlip();

		// フレームレート調整
		while (true) {
			if (GetNowHiPerformanceCount() - frameRateAdjCounter >= 1000.0f * 1000.0f / FPS_60) {
				break;
			}
		}

		prevFrameTime = frameRateAdjCounter;

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}