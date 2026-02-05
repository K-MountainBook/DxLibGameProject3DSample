// include部
#include <DxLib.h>
#include <vector>
#include <random>
#include <EffekseerForDXLib.h>

#include "Definition.h"
#include "Manager/InputManager.h"
#include "Manager/TimeManager.h"

#include "Manager/SceneManager.h"
#include "Manager/FadeManager.h"

#include "Manager/EffectManager.h"
#include "Manager/AudioManager.h"

#include "Manager/CollisionManager.h"

/*
* @brief		Windowsプログラムのエントリーポイント
* @param[in]	HINSTANCE
* @param[in]	HINSTANCE
* @param[in]	LPSTR
* @param[in]	int
* @return		int
* @tips			WinAPI
*/
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	//==========================================================
	// DxLibの初期化処理　理解するまでは触らない
	//==========================================================
	SetMainWindowText("Test");
	SetOutApplicationLogValidFlag(false);
	// ウィンドウサイズを変更する。
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, FPS);
	// 起動時のウィンドウのモードの設定
	ChangeWindowMode(TRUE);		// true ウィンドウモード
	// 背景色の設定
	SetBackgroundColor(192, 192, 192);

	// DirectXを使用します
	// effekseer自体がDirectXを使用しているため必ず必要 -> DirectX9 or 11
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// DxLibの初期化
	if (DxLib_Init() == -1) {
		return -0;
	}

	// Effekseerの初期化
	// Effekseer_Init() 引数:最大のパーティクル量
	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
		return 0;
	}

	// 描画する先を設定する　裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);


	// Effekseerを使う上でZバッファは必須
	// 図形描画のZバッファの有効化
	{
		// Zバッファを使用するか？
		SetUseZBuffer3D(TRUE);
		// Zバッファに書き込みを行うか
		SetWriteZBuffer3D(TRUE);
	}

	// ライディング
	{
		// ライトの計算をするかどうか？
		SetUseLighting(TRUE);
		// 標準ライトを使用するか？
		SetLightEnable(TRUE);
		// グローバル環境光
		SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

		//// 拡散光 diffuse
		//SetLightDifColor(GetColorF(0.25f, 0.25f, 0.25f, 1.0f));
		//// 表面反射光の設定 specular
		//SetLightSpcColor(GetColorF(0.25f, 1.0f, 0.25f, 1.0f));
		//// 環境光 Ambient
		//SetLightAmbColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
	//==========================================================
	// ゲームの初期化処理
	//==========================================================

	std::random_device rd;
	std::mt19937_64 mt(rd());
	SRand(mt());

	// シーンのインスタンス化
	// BaseScene* pGameScene = new GameScene();			マネージャを使う


	// 球の位置
	VECTOR spherePosition = VZero;
	// カメラのオイラー角
	VECTOR cameraEulerAngle = VZero;
	// 移動速度
	float moveSpeed = 10.0f;


	//==========================================================
	// ゲームのメインループ
	//==========================================================
	while (1) {
		if (ProcessMessage() == -1) {

		}

		// DxLibのカメラとEffekseerのカメラを同期する
		Effekseer_Sync3DSetting();

		//==========================================================
		// 影を表示するオブジェクトの描画
		//==========================================================

		// シャドウマップへの描画終了
		// ShadowMap_DrawEnd();

		//==========================================================
		// ゲームの更新処理の更新処理
		//==========================================================
		InputManager::GetInstance()->Update();
		TimeManager::GetInstance()->Update();
		FadeManager::GetInstance()->Update();
		EffectManager::GetInstance()->Update();
		AudioManager::GetInstance()->Update();

		if (FadeManager::GetInstance()->GetFadeState() == FadeState::FadeEnd) {
			SceneManager::GetInstance()->Update();
			CollisionManager::GetInstance()->Update();
		}

#if _DEBUG
		//ESCキーでウィンドウを閉じる
		if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_ESCAPE)) {
			break;
		}
#endif
		// 画面をクリアする
		ClearDrawScreen();


		//==========================================================
		// ゲームの描画処理（処理順に注意）
		//==========================================

#if _DEBUG
		{
			VECTOR pos1, pos2;
			//xz平面に100F毎に乱引き
			{
				// 横線
				pos1 = VGet(-5000.0f, 0.0f, -5000.0f);
				pos2 = VGet(-5000.0f, 0.0f, 5000.0f);

				for (int i = 0; i <= 100; i++) {
					DrawLine3D(pos1, pos2, gray);
					pos1.x += 100.0f;
					pos2.x += 100.0f;
				}

				//奥行の線
				pos1 = VGet(-5000.0f, 0.0f, -5000.0f);
				pos2 = VGet(5000.0f, 0.0f, -5000.0f);
				for (int i = 0; i <= 100; i++) {
					DrawLine3D(pos1, pos2, gray);
					pos1.z += 100.0f;
					pos2.z += 100.0f;
				}
			}
			{
				pos1 = VZero;
				pos2 = VScale(VRight, 5000);
				DrawLine3D(pos1, pos2, red);
			}
			{
				pos1 = VZero;
				pos2 = VScale(VUp, 5000);
				DrawLine3D(pos1, pos2, green);
			}
			{
				pos1 = VZero;
				pos2 = VScale(VForward, 5000);
				DrawLine3D(pos1, pos2, blue);
			}
		}
#endif

		//// マテリアルの設定（質感）
		//MATERIALPARAM mat;
		//mat.Diffuse = GetColorF(0.0f, 0.0f, 1.0f, 1.0f);
		//mat.Specular = GetColorF(0.25f, 0.25f, 0.25f, 0.0f);
		//mat.Ambient = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
		//mat.Emissive = GetColorF(0.1f, 0.0f, 0.0f, 1.0f);
		//mat.Power = 100;

		// ライトの計算 = ライトの拡散光 * マテリアルの拡散光
		// ライトの計算 = ライトの鏡面反射光 * マテリアルの鏡面反射光
		// ライトの計算 = ライトの環境光 * マテリアルの環境光

		//SetMaterialParam(mat);

		// モデルの描画
		// MV1DrawModel(model);
		// プレイヤーの描画
		//pPlayer->Render();
		//pCamera->Render();

		// 描画に使用するシャドウマップを設定
		//SetUseShadowMap(0, shadowMapHandle);

		// ステージの描画
		// MV1DrawModel(stageHandle);

		// キャラクターの描写
		//for (auto pGameObject : pGameObjectArray) {
		//	pGameObject->Render();
		//}


		// 常に描画する
		SceneManager::GetInstance()->Render();
		FadeManager::GetInstance()->Render();
		EffectManager::GetInstance()->Render();
		CollisionManager::GetInstance()->Render();

		// フェード処理が終了してから更新を行う
		if (FadeManager::GetInstance()->GetFadeState() == FadeState::FadeEnd) {
			CollisionManager::GetInstance()->Render();
		}
		TimeManager::GetInstance()->Render();


		// シャドウマップの設定を解放
		//SetUseShadowMap(0, -1);

		// 裏画面と表画面を切り替える
		ScreenFlip();

		// 60fpsに合わせるための空ループ
		while (1) {
			if (GetNowCount() - TimeManager::GetInstance()->GetCurrent() >= 1000.0f / FPS) {
				break;
			}

		}

	}

	// シングルトンのインスタンスを破棄
	SceneManager::DestroyInstance();	// Effect, CollisionはSceneと同時に破棄されるので記述の必要なし
	InputManager::DestroyInstance();
	TimeManager::DestroyInstance();
	FadeManager::DestroyInstance();
	AudioManager::DestroyInstance();

	// delete pGameScene;

	//==========================================================
	// DxLibの解放処理
	//==========================================================

	// effecseerの終了
	Effkseer_End();
	// dxlibの終了
	DxLib_End();

	return 0;
}