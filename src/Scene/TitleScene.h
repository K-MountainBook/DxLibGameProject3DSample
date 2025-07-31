#pragma once
#include "../Definition.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "BaseScene.h"
class TitleScene : public BaseScene
{
private:
	bool changed;
public:
	TitleScene();

	~TitleScene();

	void Start();

	void Update();

	void Render();
};

