#pragma once
#include "../Definition.h"
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
	class BaseScene* pCurrentScene;
	SceneType current;
	SceneType next;

public:
	void Update();
	void Render();
	void LoadScene();

public:
	void SetNext(SceneType _next);
};

