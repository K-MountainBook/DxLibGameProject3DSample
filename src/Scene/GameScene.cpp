#include "GameScene.h"
#include "../GameObject/Camera/Camera.h"

#include <DxLib.h>
#include <vector>

#include "../Definition.h"
#include "../GameObject/Character/Player/Player.h"

GameScene::GameScene()
	:playerModel(INVALID)
	, stageModel(INVALID)
	,shadowMapHandle(INVALID)
	,pPlayer(nullptr)
{
	Start();
	Update();
}

GameScene::~GameScene()
{
	DeleteShadowMap(shadowMapHandle);
}

void GameScene::Start()
{
	// モデルの読み込み
	playerModel = MV1LoadModel(L"Res\\Character\\Player\\PC.mv1");

	// プレイヤーのインスタンス化
	Player* pPlayer = new Player();
	{
		this->pPlayer = pPlayer;
		pPlayer->SetModelHandle(playerModel);
		// アニメの読み込み（待機モーション）
		pPlayer->GetAnimator()->Load(L"Res\\Character\\Player\\Anim_Neutral.mv1", true);
		// アニメの読み込み（走りモーション）
		pPlayer->GetAnimator()->Load(L"Res\\Character\\Player\\Anim_Run.mv1", true);
		pPlayer->GetAnimator()->Play(0);

		pGameObjectArray.push_back(pPlayer);
	}

	// TODO:カメラのインスタンス化を行う
	Camera* pCamera = new Camera(VGet(0.0f, 200.0f, -800.0f));
	{
		pCamera->SetTarget(pPlayer);
		pGameObjectArray.push_back(pCamera);
	}
}

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



	// XYZラインの描画
	// y緑、x赤、zが青
	for (int i = -5000; i <= 5000; i += 100) {
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

	// MV1DrawModel(playerModel);

	for (auto pGameObject : pGameObjectArray) {
		pGameObject->Render();
	}

}
