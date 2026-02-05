#pragma once
#include "../Definition.h"
// #include "../Collider.h"
// 循環参照になってしまう！ -> 前方宣言で回避

/*
* @brief	ゲームオブジェクトクラス
* @tips		ゲーム内に存在するモノほぼ全ての基底クラス
*/
class GameObject
{
	// private:
protected:	// メンバ変数
	bool isVisible;		// 表示・非表示フラグ
	VECTOR position;	// 座標
	VECTOR rotation;	// 回転（オイラー角）
	VECTOR scale;		// 拡縮

	MATRIX matrix;		// 座標、回転（ベクトル）、拡縮をあわせもつ行列

	class Collider* pCollider;

	std::string tag;

	VECTOR forward, right, up;	// ローカルベクトル


public:		// コンストラクタ・デストラクタ
	/*
	* @brief	コンストラクタ
	* @param[in]	VECTOR _pos = V_Zero	初期化する座標
	* @param[in]	std::string = ""
	*/
	GameObject(VECTOR _pos = VZero, std::string _tag = "");

	/*
	* @brief	デストラクタ
	* @tips		基底クラスなので仮想関数で実装する
	*/
	virtual	~GameObject();

public:
	/**
	* @function		Start
	* @brief		初期化処理
	* @tips			純粋仮想関数で実装する
	*/
	virtual void Start() = 0;
	/**
	* @function		Update
	* @brief		更新処理
	*/
	virtual void Update();
	/**
	* @function		Render
	* @brief		描画処理
	* @tips			純粋仮想関数で実装する
	*/
	virtual void Render() = 0;

public:		// 衝突検知関数
	/*
	* @function OnTriggerEnter
	* @brief	当たった瞬間
	* @param[in]	collider* _pOther	// 当たった相手
	*/

	virtual void OnTriggerEnter(class Collider* _pOther);

	/*
	* @function OnTriggerStay
	* @brief	当たっている間
	* @param[in]	collider* _pOther	// 当たった相手
	*/

	virtual void OnTriggerStay(class Collider* _pOther);

	/*
	* @function OnTriggerExit
	* @brief	抜けた瞬間
	* @param[in]	collider* _pOther	// 当たった相手
	*/

	virtual void OnTriggerExit(class Collider* _pOther);

public:		//GetterとSetter
	/*
	* @function isVisible
	* @brief	表示フラグの取得
	*/
	inline bool IsVisible() const { return isVisible; }

	/*
	* @function		SetVisible
	* @brief		表示フラグの変更
	* @param[in]	bool _v 初期化する値
	*/

	inline void SetVisible(bool _v) { isVisible = _v; }

	/*
	* @function GetPosition
	* @brief	座標の取得
	*/
	inline VECTOR GetPosition() const { return position; }

	/*
	* @function		SetPosition
	* @brief		座標の変更
	* @param[in]	VECTOR _v 変更する値
	*/

	inline void SetPosition(VECTOR _v) { position = _v; }

	/*
	* @function		SetPosition
	* @brief		座標の変更
	* @param[in]	float _x 変更するx値
	* @param[in]	float _y 変更するy値
	* @param[in]	float _z 変更するz値
	*/

	inline void SetPosition(float _x, float _y, float _z) { position = VGet(_x, _y, _z); }


	/*
	* @function		GetRotation
	* @brief		回転の変更
	* @return		VECTOR
	*/

	inline VECTOR GetRotation() const { return rotation; }

	/*
	* @function SetRotation
	* @brief	回転の変更
	* @param[in]	変更する回転角
	*/
	inline void SetRotation(VECTOR _v) { rotation = _v; }

	/*
	* @function		SetRotation
	* @brief		回転の変更
	* @param[in]	float _roll 変更するx値
	* @param[in]	float _pitch 変更するy値
	* @param[in]	float _yaw 変更するz値
	*/
	inline void SetRotation(float _roll, float _pitch, float _yaw) { position = VGet(_roll, _pitch, _yaw); }


	/*
	* @function		GetRotation
	* @brief		拡縮の取得
	* @return		VECTOR
	*/

	inline VECTOR GetScale() const { return scale; }

	/*
	* @function SetRotation
	* @brief		拡縮の変更
	*/
	inline void SetScale(VECTOR _v) { scale = _v; }

	/*
	* @function		SetScale
	* @brief		拡縮の変更
	* @param[in]	float _x 変更するx値
	* @param[in]	float _y 変更するy値
	* @param[in]	float _z 変更するz値
	*/
	inline void SetScale(float _x, float _y, float _z) { scale = VGet(_x, _y, _z); }

	/*
	* @function GetMatrix
	* @vrief	4x4行列の取得
	* @return	matrix
	*/
	inline MATRIX GetMatrix() { return matrix; }

	/*
	* @function GetCollder
	*/
	inline Collider* GetCollider() const {
		return pCollider;
	}

	/*
	* @function SetCollder
	*/
	inline void SetCollider(Collider* _pCol) {
		pCollider = _pCol;
	}

	inline std::string GetTag() const { return tag; }

	inline void SetTag(std::string _tag) {
		tag = _tag;
	}


	inline VECTOR GetForward() const {
		return forward;
	}
	inline VECTOR GetRight()  const {
		return right;
	}
	inline VECTOR GetUp() const {
		return up;
	}
};

