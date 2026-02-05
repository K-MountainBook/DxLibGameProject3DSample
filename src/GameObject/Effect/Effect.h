#pragma once
#include "../GameObject.h"

/// <summary>
/// エフェクトクラス
/// </summary>
class Effect : public GameObject {
private:		//メンバ変数
	int resourceHandle;
	int playingHandle;		// 再生中エフェクトのハンドル

public:// コンストラクタとデストラクタ
	Effect(int& _resourceHandle);

	~Effect();


public:	//オーバライドするメンバ関数

	void Start() override;

	void Update() override;

	void Render() override;

public:	// メンバ関数
public: // GetterとSetter


};

