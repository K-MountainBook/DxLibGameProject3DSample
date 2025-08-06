#pragma once
#include "../Definition.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "BaseScene.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public BaseScene
{
private:
	bool changed;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();
public:
	void Start();

	void Update();

	void Render();
};

