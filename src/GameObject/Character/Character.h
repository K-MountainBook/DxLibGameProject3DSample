#pragma once
#include "../GameObject.h"
#include "../../Component/Animator.h"
/*
* @brief    プレイヤークラス
* @tips     GameObjectクラスの派生クラス
*/

class Character : public GameObject
{
protected:	// メンバ変数
	int modelHandle;		// 3Dモデルハンドル
	Animator* pAnimator;		// アニメータークラスの宣言

public:		// コンストラクタ・デストラクタ
	/*
	* @brief	コンストラクタ
	* @param[in]	VECTOR _pos = VZero	初期化する座標
	*/
	Character(VECTOR _pos = VZero, std::string _tag = "");

	/*
	* @brief	デストラクタ
	* @tips		Player,Goblin等の基底クラスになるので、純粋仮想関数にする
	*/
	virtual ~Character();

public:			// オーバーライドしたメンバ関数


public:		// メンバ関数
	/*
	* @function		SetAnimation
	* @brief		アニメーションのセット
	* @return		int アニメーション番号
	*/
	int SetAnimation();



public:		// ゲッターとセッター
	/*
	* @function GetModelHandle
	* @brief	モデルハンドルの取得
	* @return	int
	*/
	inline int GetModelHandle() const { return modelHandle; }

	/*
	* @function SetModelHandle
	* @brief	モデルハンドルの設定
	* @param[in]	int _v 初期化するモデルハンドル
	*/
	inline void SetModelHandle(int& _v) { modelHandle = _v; }

	/*
	* @function GetAnimator
	* @brief	アニメーターの取得
	* @return	Animator*
	*/
	inline Animator* GetAnimator() const { return pAnimator; }

};

