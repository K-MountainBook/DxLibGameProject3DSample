#pragma once
#include "../Definition.h"
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

