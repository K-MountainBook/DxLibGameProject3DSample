#include "GameScene.h"
#include "../GameObject/Camera/Camera.h"
#include "../GameObject/Stage/Stage.h"

#include <DxLib.h>
#include <vector>

#include "../Definition.h"
#include "../GameObject/Character/Player/Player.h"

/// <summary>
/// コンストラクタの実装
/// </summary>
GameScene::GameScene()
	:playerModel(INVALID)
	, stageModel(INVALID)
	,shadowMapHandle(INVALID)
	,pPlayer(nullptr)
{
	Start();
}

/// <summary>
/// デストラクタの実装
/// </summary>
GameScene::~GameScene()
{
	DeleteShadowMap(shadowMapHandle);
}

void GameScene::Start()
{
	// モデルの読み込み
	playerModel = MV1LoadModel(L"Res\\Character\\Player\\PC.mv1");
	// ステージの読み込み
	stageModel = MV1LoadModel(L"Res\\Stage\\Stage01.mv1");

	// プレイヤーのインスタンス化
	Player* pPlayer = new Player();
	{
		this->pPlayer = pPlayer;

		pPlayer->SetModelHandle(playerModel);
		
		pPlayer->GetAnimator()->SetModelHandle(playerModel);
		// アニメの読み込み（待機モーション）
		pPlayer->GetAnimator()->Load(L"Res\\Character\\Player\\Anim_Neutral.mv1", true);
		// アニメの読み込み（走りモーション）
		pPlayer->GetAnimator()->Load(L"Res\\Character\\Player\\Anim_Run.mv1", true);
		
		pPlayer->GetAnimator()->Play(0);

		pGameObjectArray.push_back(pPlayer);
	}

	// カメラのインスタンス化を行う
	Camera* pCamera = new Camera(VGet(0.0f, 200.0f, -800.0f));
	{
		pCamera->SetTarget(pPlayer);
		pGameObjectArray.push_back(pCamera);
	}

	// ステージのインスタンス化
	Stage* pStage = new Stage();
	{
		pStage->SetModelHandle(stageModel);
		pStage->Register(pPlayer);

		pGameObjectArray.push_back(pStage);
	}
}

// pGameObjectArrayにぶち込んだオブジェクトを全て更新する
void GameScene::Update()
{
	for (auto pGameObject : pGameObjectArray) {
		if (pGameObject == nullptr) {
			continue;
		}
		pGameObject->Update();
	}
}

void GameScene::Render()
{
	// 背景色
	DrawBox(0, 0, 1280, 720, white, true);
#if _DEBUG
	// XYZラインの描画
	// y緑、x赤、zが青
	for (float i = -5000; i <= 5000; i += 100) {
		if (i == 0) {
			DrawLine3D(VGet(i, 0, 5000), VGet(i, 0, -5000), blue);	// Z
			DrawLine3D(VGet(5000, 0, i), VGet(-5000, 0, i), red);	// X
		}
		else {
			DrawLine3D(VGet(i, 0, 5000), VGet(i, 0, -5000), gray);	// Z
			DrawLine3D(VGet(5000, 0, i), VGet(-5000, 0, i), gray);	// X
		}
		// DrawLine3D(VGet(0, 10000, i), VGet(0, -10000, i), gray);	// Y

	}
#endif
	// pGameObjectArrayにぶち込んだオブジェクトを全てレンダリングする
	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}

}
