#include "SceneManager.h"
#include "../Scene/GameScene.h"
#

SceneManager* SceneManager::pInstance = nullptr;

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

void SceneManager::CreateInstance()
{
	pInstance = new SceneManager();
}

SceneManager* SceneManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}

	return pInstance;
}

void SceneManager::DestroyInstance()
{
}


void SceneManager::SetNext(SceneType _next)
{
	next = _next;
}

void SceneManager::Update() {
	if (pCurrentScene == nullptr) {
		return;
	}
	
	pCurrentScene->Update();

	// ê–Ê‚Ì‘JˆÚ‚ª–³‚¯‚ê‚ÎXV‚µ‚È‚¢
	if (current != next) {
		LoadScene();
	}

}

void SceneManager::Render() {

	if (pCurrentScene == nullptr) {
		return;
	}

	pCurrentScene->Render();
}

void SceneManager::LoadScene()
{
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

	current = next;
}
