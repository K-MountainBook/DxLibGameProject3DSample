#pragma once
#include "../GameObject.h"
#include <vector>
/*
* @brief ステージクラス
* @tips ゲームオブジェクトクラスの派生
*/
class Stage : public GameObject
{
private:	// メンバ変数
	int modelHandle;								// モデルハンドル
	std::vector<GameObject*> onGroundObjectArray;	// 地面に接地するオブジェクト達

public:		//　コンストラクタとデストラクタ
	Stage();

	~Stage();

public:		// オーバーライドするメンバ関数

	void Start() override;

	void Update() override;

	void Render() override;

public:		// メンバ関数
	/*
	* @function Register
	* @brief 接地オブジェクトとして登録
	* @param[in]	GameObject* _pObj
	*/
	void Register(GameObject* _pObj);

public:

	/*
	* @function SetModelHandle
	* @brief	モデルハンドルの設定
	* @param[in]	int _v 初期化するモデルハンドル
	*/
	inline void SetModelHandle(int& _v) { modelHandle = _v; }


};
