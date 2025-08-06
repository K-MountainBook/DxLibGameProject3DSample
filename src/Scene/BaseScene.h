#pragma once

#include <vector>
#include "../GameObject/GameObject.h"

/// <summary>
/// ベースのシーン
/// </summary>
class BaseScene {

protected:
	std::vector<GameObject*> pGameObjectArray;	// シーンに登録するゲームオブジェクト

public:
	// コンストラクタ
	BaseScene() = default;

	// デストラクタ
	virtual ~BaseScene() {
		for (auto pObj : pGameObjectArray) {
			delete pObj;
			pObj = nullptr;
		}
	}

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};