#include "TitleScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
	:BaseScene()
	, changed(false)
{
	Start();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
}

/// <summary>
/// 初期化
/// </summary>
void TitleScene::Start()
{
}

/// <summary>
/// データの更新
/// </summary>
void TitleScene::Update()
{
	if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)){
		SceneManager::GetInstance()->SetNext(SceneType::Game);
	}
}

/// <summary>
/// 描画
/// </summary>
void TitleScene::Render()
{

}
