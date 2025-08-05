#pragma once
#include "BaseScene.h"
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
	GameScene();

	~GameScene();

public:
	void Start() override;
	void Update() override;
	void Render() override;
};

