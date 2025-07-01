#pragma once
#include "../Definition.h"

class GameObject
{
protected:
	bool isVisible;				// 表示フラグ
	VECTOR position;			// 位置
	VECTOR rotation;			// 回転（オイラー
	VECTOR scale;				// 拡縮

	MATRIX matrix;				// 座標、回転、拡縮行列

	std::string tag;

	VECTOR forward, right, up;	// ローカルベクトル

public:
	// コンストラクタ
	GameObject(VECTOR _pos = VZero, std::string _tag = "");
	// デストラクタ
	~GameObject();

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
public:	
	// Getter and Setter
	inline void SetVisible(bool _v) { isVisible = _v; };

	inline bool IsVisible() { return isVisible; };

	inline VECTOR GetPosition() const { return position; };

	inline void SetPosition(float _x, float _y, float _z) { position = VGet(_x, _y, _z); };

	inline VECTOR GetRotation() const { return rotation; };

	inline void SetRotation(float _roll, float _pitch, float _yaw) { rotation = VGet(_roll, _pitch, _yaw); };

	inline VECTOR GetScale() const { return scale; };

	inline void SetScale(VECTOR _v) { scale = _v; };

	inline MATRIX GetMatrix() const { return matrix; };

};

