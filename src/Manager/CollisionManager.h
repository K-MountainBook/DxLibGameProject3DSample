#pragma once
#include <vector>
#include <DxLib.h>

/*
* @brief	当たり判定の管理
* @tips		シングルトン
*/
class CollisionManager
{
#pragma region シングルトンのデータ構造

private:
	static CollisionManager* pInstance;
private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	CollisionManager();

	/*
	* @brief デストラクタ
	*/
	~CollisionManager();

public:		// コピーと譲渡の禁止
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager(CollisionManager&&) = delete;

	CollisionManager& operator = (const CollisionManager&) = delete;
	CollisionManager& operator = (CollisionManager&&) = delete;


private:	// 静的メンバ関数
	/*
	* @function	CreateInstance
	* @brief	自身のインスタンスを生成する。
	*/
	static void CreateInstance();


public:		// 静的メンバ関数
	/*
	* @function GetInstance
	* @brief	自身のインスタンスを取得する唯一の手段
	* @return	InputManager*	自身のインスタンスのアドレス
	*/
	static CollisionManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();

#pragma endregion

private:
	std::vector<class Collider*> pColliderArray;			//当たり判定の一元管理
	std::vector<std::vector<bool>> prevs;							// 1フレーム前の衝突結果
	std::vector<std::vector<bool>> currents;							// 現在の衝突結果
	int index;
public:		// メンバ関数

	void Render();


	/*
	* @function	Update
	* @brief	更新処理
	*/
	void Update();

	/*
	* @function	Register
	* @brief	一元管理に登録する
	* @param[in]	Collider*	_pCol	登録する当たり判定
	*/
	void Register(class Collider* _pCol);

	/*
	* @function	UnRegister
	* @brief	一元管理に登録する
	* @param[in]	Collider*	_pCol	登録する当たり判定
	*/
	void UnRegister(class Collider* _pCol);



	/*
	* @function	CheckHit
	* @brief	当たり判定の衝突検知
	* @param[in]	Collider* _pCol1	当たり判定1
	* @param[in]	Collider* _pCol2	当たり判定2
	* @return		bool
	*/
	bool CheckHit(class Collider* _pCol1, class Collider* pCol2);
};

