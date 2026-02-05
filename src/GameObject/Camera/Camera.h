#pragma once
#include "../GameObject.h"

/*
* @brief    カメラクラス
* @tips     GameObjectクラスの派生クラス
*/
class Camera : public GameObject
{
private:	// メンバ変数
	GameObject* pTarget;	// 追従対象のポインタ
	float armLength;		// 追従対象との距離

	VECTOR offset;			// 位置調整用

	VECTOR shakeOffset;		// 揺れ調整用
	VECTOR shakePattern;	// 実際に揺らす揺れ
	float timer;			// 時間計測用
	float shakeTime;			// 揺れ時間

	bool isShaking;			// 揺れ中かどうか

public:		// 静的メンバ変数
	static Camera* main;


public:		// コンストラクタ・デストラクタ
	/*
	* @brief	コンストラクタ
	* @param[in]	VECTOR _pos = VZero
	* @param[in]	float _length = 500.0f
	*/
	Camera(VECTOR _pos = VZero, float _length = 500.0f);

	/*
	* @brief	デストラクタ
	*/
	~Camera();

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

public:		//メンバ関数
	/*
	* @function Shake
	* @brief	カメラのシェイク、揺れ
	* @param[in]	int _direction 揺れの方向	0:横,1:縦,2:両方
	* @param[in]	float _time		揺れの長さ
	* @param[in]	float _power = 0.25f	揺れの強さ
	*/
	void Shake(int _direction, float _time, float _power = 0.25f);

public:
	/*
	* @function		GetTarget
	* @brief		追従する対象の取得
	* @return		GameObject*
	*/
	inline GameObject* GetTraget() const { return pTarget; }

	/*
	* @function		GetTarget
	* @brief		追従する対象のhhaiti
	* @param[out]	初期化する追従の対象
	*/
	inline void SetTarget(GameObject* _v) { pTarget = _v; }
};

