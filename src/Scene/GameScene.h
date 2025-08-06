#pragma once
#include "BaseScene.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public BaseScene
{
protected:
	int playerModel;
	int enemyModel;
	int stageModel;
	int playerWeaponModel;
	int enemyWeaponModel;

	int shadowMapHandle;
	const VECTOR shadowOffset = VGet(512, 512, 512);

	GameObject* pPlayer;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

public:
	void Start() override;
	void Update() override;
	void Render() override;
};

