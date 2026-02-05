#include "SceneManager.h"
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"
#include "FadeManager.h"

/*
 * @brief 入力管理クラス
 * @tips 管理するクラスは1つであるべき -> シングルトンのデータ構造
 */

SceneManager* SceneManager::pInstance = nullptr;

SceneManager::SceneManager()
	:pCurrentScene(nullptr)
	, next(SceneType::Title)
	, current((SceneType)INVALID)
{
	// 遷移先のシーンを生成する
	switch (next)
	{
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}

	current = next;
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

void SceneManager::Update()
{

	// シーンが無ければ更新しない
	if (pCurrentScene == nullptr) {
		return;
	}
	// 現在のシーンを更新する
	pCurrentScene->Update();

	// シーンの切り替えがあれば遷移を行う
	if (current != next) {
		LoadScene();
	}
}

void SceneManager::Render()
{

	// シーンが無ければ更新しない
	if (pCurrentScene == nullptr) {
		return;
	}
	// 現在のシーンを更新する
	pCurrentScene->Render();

}

void SceneManager::LoadScene()
{
	// 現在のシーン番号を書き換える
	current = next;


	delete pCurrentScene;
	pCurrentScene = nullptr;

	// 次のシーンを生成する
	switch (next)
	{
	case SceneType::Title:
		pCurrentScene = new TitleScene();
		break;
	case SceneType::Game:
		pCurrentScene = new GameScene();
		break;
	default:
		pCurrentScene = nullptr;
		break;
	}
}

void SceneManager::SetNext(SceneType _next)
{
	next = _next;
}
