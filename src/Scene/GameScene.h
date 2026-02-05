#pragma once
#include "BaseScene.h"
class GameScene : public BaseScene
{
protected:
	int playerModel;				// プレイヤーモデルハンドラ
	int playerWeaponModel;			// プレイヤー武器モデルハンドラ
	int goblinModel;				// 敵モデルハンドラ
	int goblinWeaponModel;			// 敵武器モデルハンドラ
	int stageModel;					// ステージハンドラ

	int shadowMapHandle;			// シャドウマップハンドラ
	const VECTOR shadowOffset = VGet(512, 512, 512);	// 影の描画調整用

	
	GameObject* pPlayer;				// 影描画中心点のため

public:
	// コンストラクタ
	GameScene();
	// デストラクタ
	~GameScene();
public:
	void Start()  override;
	void Update() override;
	void Render() override;
};


