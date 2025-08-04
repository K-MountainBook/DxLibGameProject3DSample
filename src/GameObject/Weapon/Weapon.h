#pragma once
#include "../GameObject.h"

/// <summary>
/// •ŠíƒNƒ‰ƒX
/// </summary>
class Weapon : public GameObject
{
private:
	int modelHandle;
	int attachiModelHandle;
	int attachiFrameIndex;
	bool isAttacking;

public:
	Weapon(std::string _tag = "");

	~Weapon();

public:
	void Start() override;

	void Update() override;

	void Render() override;

public:

	void Attach(int& _attachiModel, int& _weaponModel, std::wstring _frameName);

};

