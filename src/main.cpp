﻿#include <DxLib.h>
#include "Definition.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int model1, anim_nutral, anim_run, attachidx, rootflm;
	float anim_totaltime, playtime = 0.0f;
	int key;
	// プレイヤーの位置
	VECTOR pos = VGet(640.0f, 280.0f, -400.0f);
	// カメラポジション
	VECTOR cpos = VGet(640.0f, 480.0f, -800.0f);
	// 注視点
	VECTOR ctgt = VGet(640.0f, 280.0f, -400.0f);
	bool running = false;


	enum Direction {
		DOWN,
		LEFT,
		UP,
		RIGHT
	} direction = DOWN;
	MATRIX mat1, mat2;

	SetGraphMode(WINDOW_WIDTH_HD, WINDOW_HEIGHT_HD, 32, FPS_60);
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// フレームレート調整用カウンタ（ミリ秒
	int frameRateAdjCounter;
	float fps = 0.0f;

	// モデルの読み込み
	model1 = MV1LoadModel(L"Res\\Character\\Player\\PC.mv1");
	// アニメの読み込み（待機モーション）
	anim_nutral = MV1LoadModel(L"Res\\Character\\Player\\Anim_Neutral.mv1");
	// アニメの読み込み（走りモーション）
	anim_run = MV1LoadModel(L"Res\\Character\\Player\\Anim_Run.mv1");
	// アニメーションのアタッチ（待機モーション
	attachidx = MV1AttachAnim(model1, 0, anim_nutral);
	// アニメーションの総再生時間を取得
	anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
	// モデルの"root"フレームを取得
	rootflm = MV1SearchFrame(model1, L"root");
	// 単位行列の初期値を取得し移動しないようにする。
	MV1SetFrameUserLocalMatrix(model1, rootflm, MGetIdent());

	// 書き込み先をバックバッファに設定
	SetDrawScreen(DX_SCREEN_BACK);

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(cpos, ctgt, VGet(0.0f, 1.0f, 0.0f));

	if (model1 == -1) {
		return -1;
	}

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		frameRateAdjCounter = GetNowCount();

		// アニメの再生時間を加算する
		playtime += 0.5f;
		// トータル時間を超過した場合リセットする
		if (playtime > anim_totaltime) {
			playtime = 0.0f;
		}

		MV1SetAttachAnimTime(model1, attachidx, playtime);

		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key & PAD_INPUT_DOWN) {
			pos.z -= 4.0f;
			direction = DOWN;
		}
		if (key & PAD_INPUT_UP) {
			pos.z += 4.0f;
			direction = UP;
		}
		if (key & PAD_INPUT_LEFT) {
			pos.x -= 4.0f;
			direction = LEFT;
		}
		if (key & PAD_INPUT_RIGHT) {
			pos.x += 4.0f;
			direction = RIGHT;
		}
		if (key == 0) {
			if (running == true) {
				running = false;
				MV1DetachAnim(model1, attachidx);
				attachidx = MV1AttachAnim(model1, 0, anim_nutral);
				anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
			}
		}
		else {
			if (running == false) {
				running = true;
				MV1DetachAnim(model1, attachidx);
				attachidx = MV1AttachAnim(model1, 0, anim_run);
				anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
			}
		}

		ClearDrawScreen();
		// メイン処理を記載
		DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);

		MV1SetRotationXYZ(model1, VGet(0.0f, DX_PI / 2 * direction, 0.0f));
		MV1SetPosition(model1, pos);
		// mat1 = MGetRotY(DX_PI / 2 * direction);
		// mat2 = MGetTranslate(pos);
		// MV1SetMatrix(model1, MMult(mat1, mat2));

		MV1DrawModel(model1);

		fps = 1000.0f / (GetNowCount() - frameRateAdjCounter);

		DrawFormatString(0, 0, red, L"FPS:%.2f", fps);

		// スクリーンバッファの入れ替え
		ScreenFlip();

		// フレームレート調整
		while (1) {
			if (GetNowCount() - frameRateAdjCounter >= 1000 / FPS_60) {
				break;
			}
		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}