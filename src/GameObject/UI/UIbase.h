#pragma once
#include "../GameObject.h"
class UIbase : public GameObject
{
private:
	GameObject* pGameObject;
public:
	UIbase(GameObject* _pObj);

	~UIbase();
};

