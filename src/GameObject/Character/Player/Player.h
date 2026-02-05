#pragma once
#include "../Character.h"
#include "../../Weapon/Weapon.h"
#include "../../../Component/Collider.h"

/*
* @brief    プレイヤークラス
* @tips     GameObjectクラスの派生クラス
*/

class Player : public Character
{
	// メンバ変数
private:
	bool isAttacking;	// 攻撃中

	Weapon* pWeapon;

public:		// コンストラクタ・デストラクタ
	/*
	* @brief	コンストラクタ
	* @param[in]	VECTOR _pos = VZero	初期化する座標
	*/
	Player(VECTOR _pos = VZero);

	/*
	* @brief	デストラクタ
	*/
	~Player();

public:			// オーバーライドしたメンバ関数
	/**
	* @function		Start
	* @brief		初期化処理
	* @tips			純粋仮想関数で実装する
	*/
	void Start() override;
	/**
	* @function		Update
	* @brief		更新処理
	* @tips			純粋仮想関数で実装する
	*/
	void Update() override;
	/**
	* @function		Render
	* @brief		描画処理
	* @tips			純粋仮想関数で実装する
	*/
	void Render() override;

	void OnTriggerEnter(Collider* _pCol) override;

	void OnTriggerStay(Collider* _pCol) override;

	void OnTriggerExit(Collider* _pCol) override;

public:		// メンバ関数


public:		// ゲッターとセッター
	/*
	* @function		GetWeapon
	* @brief		武器の取得
	*/
	inline Weapon* GetWeapon() const { return pWeapon; }

	inline void SetWeapon(Weapon* weapon) {
		pWeapon = weapon;
	}
};

