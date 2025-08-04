#pragma once
#ifndef UNIQUE_SCENEMANAGER
#define UNIQUE_SCENEMANAGER


#include "../Definition.h"
#include <string>

/// <summary>
/// シーン管理クラス（シングルトン）
/// </summary>
class SceneManager
{
private:
	static SceneManager* pInstance;

private:

	SceneManager();

	~SceneManager() = default;

public:

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;

	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

private:
	static void CreateInstance();

public:
	static SceneManager* GetInstance();

	static void DestroyInstance();

	
private:
	// メンバ変数
	class BaseScene* pCurrentScene;
	SceneType current;
	SceneType next;

public:
	void Update();
	void Render();
	void LoadScene();

public:
	void SetNext(SceneType _next);

	std::wstring GetCurrentScene() {
		std::wstring temp = L"";
		switch (current)
		{
		case SceneType::Title:
			temp = L"Title";
			break;
		case SceneType::Game:
			temp = L"Game";
			break;
		case SceneType::Clear:
			temp = L"Clear";
			break;
		case SceneType::GameOver:
			temp = L"GameOver";
			break;
		default:
			break;
		}
		return temp;
	}
};


#endif // !UNIQUE SCENEMANAGER