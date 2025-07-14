#pragma once
#include "../GameObject.h"
#include "../../Component/Animator.h"

/// <summary>
/// キャラクタクラス
/// </summary>
class Character : public GameObject
{
protected:
	int modelHandle;		// モデルのハンドル
	Animator* pAnimator;	// アニメータ

public:
	// コンストラクタ
	Character(VECTOR _pos = VZero, std::string _tag = "");
	// デストラクタ
	virtual ~Character();

public:

	// モデルハンドルの設定
	void SetModelHandle(int& handle) { modelHandle = handle; }

	// モデルハンドルのｓ取得
	inline int GetModelHandle() { return modelHandle; }

	inline Animator* GetAnimator() const { return pAnimator; }

};

