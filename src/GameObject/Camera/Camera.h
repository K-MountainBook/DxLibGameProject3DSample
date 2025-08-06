#pragma once
#include "../GameObject.h"
class Camera : public GameObject
{
private:
	GameObject* pTarget;	// 追従対象のポインタ
	float armLength;		// 追従対象との距離

	VECTOR offset;			// 位置

	VECTOR shakeOffset;		// 揺れの調整
	VECTOR shakePattern;	// 実際の揺れ
	float timer;			// 時間計測用
	float shakeTime;		// 揺れ時間

	bool isShaking;			// 揺れ中？

	short LStickX;
	short LStickY;
	short RStickX;
	short RStickY;

	unsigned char LTrigger;	
	unsigned char RTrigger;

public:
	static Camera* main;	// メインカメラ

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">座標</param>
	/// <param name="_length">カメラの距離</param>
	Camera(VECTOR _pos = VZero, float _length = 500.0f);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Camera();

public:
	void Start() override;

	void Update() override;

	void Render() override;

public:
	/// <summary>
	/// 画面の揺れ
	/// </summary>
	/// <param name="_direction"></param>
	/// <param name="_time"></param>
	/// <param name="_power"></param>
	void Shake(int _direction, float _time, float _power = 0.25f);

	/// <summary>
	/// カメラターゲットの取得
	/// </summary>
	/// <returns>GameObject*</returns>
	inline GameObject* GetTarget() const { return pTarget; }

	/// <summary>
	/// カメラターゲットのセット
	/// </summary>
	/// <param name="_v">GameObject継承クラス</param>
	inline void SetTarget(GameObject* _v) { pTarget = _v; }
};

