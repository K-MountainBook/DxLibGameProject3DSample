#pragma once

#include <vector>
#include "../GameObject/GameObject.h"
#include "../Manager/EffectManager.h"
#include "../Manager/CollisionManager.h"


class BaseScene {
protected:
	std::vector<GameObject*> pGameObjectArray;

public:
	BaseScene() = default;

	virtual ~BaseScene() {

		for (auto pObj : pGameObjectArray) {
			delete pObj;
			pObj = nullptr;
		}

		//当たり判定の登録も初期化
		CollisionManager::DestroyInstance();
		// 使用中のエフェクトも初期化
		EffectManager::DestroyInstance();

	}

public:

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};
