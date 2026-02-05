#pragma once
#include "../Definition.h"
class SceneManager
{
#pragma region シングルトンのデータ構造
private:
	static SceneManager* pInstance;

private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	SceneManager();

	/*
	* @brief デストラクタ
	*/
	~SceneManager() = default;

public:		// コピーと譲渡の禁止
	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;

	SceneManager& operator = (const SceneManager&) = delete;
	SceneManager& operator = (SceneManager&&) = delete;

private:	// 静的メンバ関数
	/*
	* @function	CreateInstance
	* @brief	自身のインスタンスを生成する。
	*/
	static void CreateInstance();

public:		// 静的メンバ関数
	/*
	* @function GetInstance
	* @brief	自身のインスタンスを取得する唯一の手段
	* @return	InputManager*	自身のインスタンスのアドレス
	*/
	static SceneManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();


#pragma endregion
private:	//	メンバ変数
	class BaseScene* pCurrentScene;			// 現在のシーン
	SceneType current;						// 現在のシーン番号
	SceneType next;							// 次のシーン番号


public:		// メンバ関数

	void Update();

	void Render();

	/*
	* @funtion	LoadScene
	* @brief	シーン遷移
	*/
	void LoadScene();

public:		// アクセッサ

	/*
	* @function SetNext
	*/
	void SetNext(SceneType _next);

};

