#pragma once
#include "../Definition.h"

class GameObject
{
protected:
	bool isVisble;				// 表示フラグ
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

};

