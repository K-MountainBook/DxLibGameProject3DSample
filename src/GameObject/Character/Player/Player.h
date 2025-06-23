#pragma once
#include "../Character.h"
class Player : public Character
{
public:
	
	// コンストラクタ
	Player(VECTOR _pos = VZero);

	// デストラクタ
	~Player();

protected:
	XINPUT_STATE xinput;
	int inputX, inputY;
	int key;
	bool running = false;

	int model;



public:
	void Start() override;

	void Update() override;

	void Render() override;
};

