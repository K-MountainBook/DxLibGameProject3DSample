#include "SceneManager.h"
#include "../Scene/GameScene.h"
#

SceneManager* SceneManager::pInstance = nullptr;

/// <summary>
/// コンストラクタ（初めのシーンを設定する）
/// </summary>
SceneManager::SceneManager()
    :pCurrentScene(nullptr)
	, next(SceneType::Game)
	, current((SceneType)INVALID)
{
	switch (next)
	{
	case SceneType::Title:
		pCurrentScene = nullptr;
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene;
		break;
	case SceneType::Clear:
		pCurrentScene = nullptr;
		break;
	case SceneType::GameOver:
		pCurrentScene = nullptr;
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}
}

/// <summary>
/// インスタンスの作成
/// </summary>
void SceneManager::CreateInstance()
{
	pInstance = new SceneManager();
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
SceneManager* SceneManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}

	return pInstance;
}

/// <summary>
/// インスタンスの破棄
/// </summary>
void SceneManager::DestroyInstance()
{
}

/// <summary>
/// 次のシーンを設定する
/// </summary>
/// <param name="_next">SceneType</param>
void SceneManager::SetNext(SceneType _next)
{
	next = _next;
}

/// <summary>
/// シーンの状態をUpdate
/// また、次のシーンが設定されていればシーン遷移と読み込みを行う
/// </summary>
void SceneManager::Update() {
	if (pCurrentScene == nullptr) {
		return;
	}
	
	pCurrentScene->Update();

	// 場面の遷移が無ければ更新しない
	if (current != next) {
		LoadScene();
	}

}

/// <summary>
/// シーンのレンダリング
/// </summary>
void SceneManager::Render() {

	if (pCurrentScene == nullptr) {
		return;
	}

	pCurrentScene->Render();
}

/// <summary>
/// シーンの読み込み
/// </summary>
void SceneManager::LoadScene()
{

	current = next;

	delete pCurrentScene;

	pCurrentScene = nullptr;

	switch (next)
	{
	case SceneType::Title:
		pCurrentScene = nullptr;
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene;
		break;
	case SceneType::Clear:
		pCurrentScene = nullptr;
		break;
	case SceneType::GameOver:
		pCurrentScene = nullptr;
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}

}
