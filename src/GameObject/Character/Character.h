#pragma once
#include "../GameObject.h"
#include "../../Component/Animator.h"

class Character : public GameObject
{
protected:
	int modelHandle;
	Animator* pAnimator;

public:
	// コンストラクタ
	Character(VECTOR _pos = VZero, std::string _tag = "");
	// デストラクタ
	virtual ~Character();

public:

	// モデルハンドルの設定
	void SetModelHandle(int handle) { modelHandle = handle; }

	// モデルハンドルのｓ取得
	int GetModelHandle() { return modelHandle; }

	inline Animator* GetAnimator() const { return pAnimator; }

};

