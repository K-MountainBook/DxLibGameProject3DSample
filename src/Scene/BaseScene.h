#pragma once

#include <vector>
#include "../GameObject/GameObject.h"

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
	}

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};