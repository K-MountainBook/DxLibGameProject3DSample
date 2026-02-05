#pragma once
#include "../Definition.h"

/// <summary>
/// フェード管理
/// </summary>
class FadeManager
{
#pragma region シングルトンのデータ構造
private:
	static FadeManager* pInstance;

private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	FadeManager();

	/*
	* @brief デストラクタ
	*/
	~FadeManager();

public:		// コピーと譲渡の禁止
	FadeManager(const FadeManager&) = delete;
	FadeManager(FadeManager&&) = delete;

	FadeManager& operator = (const FadeManager&) = delete;
	FadeManager& operator = (FadeManager&&) = delete;

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
	static FadeManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();


#pragma endregion

private:
	float blend;		// ブレンドパラメータ 0~255 0:透明 255:不透明
	float time;			// 経過時間観察用
	FadeState fadeState;	// FadeState

public:

	void Update();

	void Render();

	/// <summary>
	/// フェードイン（暗→明）
	/// </summary>
	/// <param name="_t"></param>
	void FadeIn(float _t = 1.0f);

	/// <summary>
	/// フェードアウト（明→暗）
	/// </summary>
	/// <param name="_t"></param>
	void FadeOut(float _t = 1.0f);
public:

	inline FadeState GetFadeState() const { return fadeState; }

};

