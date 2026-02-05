#pragma once
#include "../GameObject.h"

/*
* @brief 武器クラス
*/
class Weapon : public GameObject
{
private:
	int modelHandle;		// 武器のモデルハンドル
	int attachModelHandle;	// 武器を持たせるモデルハンドル
	int attachFrameIndex;	// 武器を持たせるフレーム番号
	bool isAttacking;

public:	// コンストラクタ・デストラクタ
	/*
	* @brief コンストラクタ
	* @param[in]	std::string _tag = ""
	*/
	Weapon(std::string _tag = "");


	/*
	* @brief デストラクタ
	* @tips		継承して使うときは仮想関数にする。
	*/
	~Weapon();

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
	/*
	* @function	Attach
	* @brief	武器を取り付ける、持たせる
	* @param[in]	int&	_attachiModel	持たせるモデルハンドル
	* @param[in]	int&	_weaponModel	武器のモデルハンドル
	* @param[in]	std::string	_frameName	アタッチするフレーム名
	*/
	void Attach(int& _attachiModel, int& _weaponModel, std::string _frameName);

public:		// ゲッターとセッター
	void setIsAttacking(bool _p) {
		isAttacking = _p;
	}

	bool getIsAttacking() {
		return isAttacking;
	}

};

