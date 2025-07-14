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
	int key;
	bool running = false;

public:
	void Start() override;

	void Update() override;

	void Render() override;
};

