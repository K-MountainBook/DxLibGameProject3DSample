#include "GameScene.h"
// include部
#include <DxLib.h>
#include <vector>
#include <random>

#include "../Definition.h"
#include "../Manager/InputManager.h"

#include "../GameObject/Character/Player/Player.h"
#include "../GameObject/Character/Enemy/Goblin/Goblin.h"
#include "../GameObject/Camera/Camera.h"
#include "../GameObject/Stage/Stage.h"

GameScene::GameScene()
	:playerModel(INVALID)
	, playerWeaponModel(INVALID)
	, goblinModel(INVALID)
	, goblinWeaponModel(INVALID)
	, stageModel(INVALID)
	, shadowMapHandle(INVALID)
	, pPlayer(nullptr)
{
	Start();
	Update();
}

GameScene::~GameScene()
{
	// シャドウマップの解放
	DeleteShadowMap(shadowMapHandle);

}

void GameScene::Start()
{
	// モデルの読み込み
	playerModel = MV1LoadModel("Res/Character/Player/maya_PlayerCharacter.MV1");
	playerWeaponModel = MV1LoadModel("Res/Character/Weapon/Sabel/sabel.mv1");
	goblinModel = MV1LoadModel("Res/Character/Goblin/Goblin.mv1");
	goblinWeaponModel = MV1LoadModel("Res/Character/Weapon/Axe/Axe.mv1");
	stageModel = MV1LoadModel("Res/Stage/Stage00.mv1");

	// プレイヤーのインスタンス化
	Player* pPlayer = new Player();
	{
		//プレイヤーの中心点を取得
		// playerPos = &pPlayer->GetPosition();
		this->pPlayer = pPlayer;

		pPlayer->SetModelHandle(playerModel);
		// プレイヤーのアニメーターのモデルデータのセット
		pPlayer->GetAnimator()->SetModelHandle(playerModel);
		// アニメーションの読み込み
		pPlayer->GetAnimator()->Load("Res/Character/Player/Neutral.mv1", true);
		pPlayer->GetAnimator()->Load("Res/Character/Player/maya_Run.mv1", true);
		pPlayer->GetAnimator()->Load("Res/Character/Player/maya_Attack1.mv1");
		// アニメーションの再生
		pPlayer->GetAnimator()->Play(0);
		// プレイヤーに当たり判定をセット
		// pPlayer->SetCollider(new BoxCollider(pPlayer, VGet(-100, 0, -100), VGet(100, 200, 100)));
		pPlayer->SetCollider(new CapsuleCollider(pPlayer, VZero, VScale(VUp, 120), 30.0));
		// 当たり判定を登録
		CollisionManager::GetInstance()->Register(pPlayer->GetCollider());

		// プレイヤーの武器のインスタンス化
		Weapon* pSabel = new Weapon();

		// プレイヤーの武器をセットしてあげる
		pPlayer->SetWeapon(pSabel);
		// プレイヤーの武器を所定の位置にアタッチ
		pPlayer->GetWeapon()->Attach(playerModel, playerWeaponModel, "wp");
		// 武器の当たり判定をセット
		pPlayer->GetWeapon()->SetCollider(new CapsuleCollider(pPlayer->GetWeapon(), VZero, VScale(VDown, 100), 10.0f));
		CollisionManager::GetInstance()->Register(pPlayer->GetWeapon()->GetCollider());
		// 一元管理する配列に追加。
		pGameObjectArray.push_back(pPlayer->GetWeapon());
		pGameObjectArray.push_back(pPlayer);
	}

	// カメラのインスタンス化
	Camera* pCamera = new Camera(VGet(0.0f, 200.0f, -800.0f));
	{
		// カメラの追従対象
		pCamera->SetTarget(pPlayer);

	}
	// 一元管理する配列に追加。
	pGameObjectArray.push_back(pCamera);

	// ゴブリンのインスタンス化
	Goblin* pGoblin = new Goblin(VGet(0.0f, 0.0f, 400.0f));
	{
		pGoblin->SetModelHandle(goblinModel);
		// ゴブリンのアニメーターのモデルデータのセット
		pGoblin->GetAnimator()->SetModelHandle(goblinModel);
		// アニメーションの読み込み
		pGoblin->GetAnimator()->Load("Res/Character/Goblin/Neutral.MV1", TRUE);
		pGoblin->GetAnimator()->Load("Res/Character/Goblin/Attack1.MV1");

		// アニメーションの再生
		pGoblin->GetAnimator()->Play(0);

		// ゴブリン自体の当たり判定
		pGoblin->SetCollider(new CapsuleCollider(pGoblin, VZero, VScale(VUp, 100), 30.0f));

		// 当たり判定登録
		CollisionManager::GetInstance()->Register(pGoblin->GetCollider());

		// ゴブリンへ武器を持たせる
		Weapon* pAxe = new Weapon();
		pGoblin->SetWeapon(pAxe);

		pGoblin->GetWeapon()->Attach(goblinModel, goblinWeaponModel, "hansocketR");

		pGoblin->GetWeapon()->SetCollider(new CapsuleCollider(pGoblin->GetWeapon(), VZero, VScale(VUp, 75), 10.0f));

		// 当たり判定を登録
		CollisionManager::GetInstance()->Register(pGoblin->GetWeapon()->GetCollider());


	}
	pGameObjectArray.push_back(pGoblin);

	// エフェクトの読み込み
	EffectManager::GetInstance()->Load("Res/Effect/boss_death.efkefc", "BossDeath", 5.0f);
	EffectManager::GetInstance()->Load("Res/Effect/hit.efkefc", "Hit", 10.0f);

	// ステージのインスタンス化
	Stage* pStage = new Stage();
	{
		pStage->SetModelHandle(stageModel);

		pStage->Register(pPlayer);
		pStage->Register(pGoblin);
	}
	// 一元管理配列に追加、描画順の関係でに追加
	pGameObjectArray.emplace(pGameObjectArray.begin(), pStage);

	// シャドウマップハンドルの作成
	{
		shadowMapHandle = MakeShadowMap(512, 512);
		// デバッグ用の影を出すための光
		SetLightDirection(VDown);
		// シャドウマップのライトの設定
		SetShadowMapLightDirection(shadowMapHandle, VDown);
	}
}

void GameScene::Update()
{
	// 一元管理されているオブジェクトの更新
	for (auto pGameObject : pGameObjectArray)
	{
		// nullptrチェック
		if (pGameObject == nullptr) {
			continue;
		}
		pGameObject->Update();

		// 当たり判定があるなら追加で更新
		if (pGameObject->GetCollider() != nullptr) {
			pGameObject->GetCollider()->Update();
		}
	}
}

void GameScene::Render()
{
	// 影を描画する範囲の設定
	SetShadowMapDrawArea(
		shadowMapHandle,
		VSub(pPlayer->GetPosition(), shadowOffset),
		VAdd(pPlayer->GetPosition(), shadowOffset)
	);
	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(shadowMapHandle);

	// 3Dモデルの読み込み
	MV1DrawModel(stageModel);
	MV1DrawModel(playerModel);
	MV1DrawModel(playerWeaponModel);
	MV1DrawModel(goblinModel);
	MV1DrawModel(goblinWeaponModel);

	// シャドウマップへの描画終了
	ShadowMap_DrawEnd();

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

	// 描画に使用するシャドウマップを設定
	SetUseShadowMap(0, shadowMapHandle);
	// キャラクターの描写
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}

	// エフェクトの描写
	// EffectManager::GetInstance()->Render();

	// UIの読み込み


	// シャドウマップの設定を解放
	SetUseShadowMap(0, -1);
}
