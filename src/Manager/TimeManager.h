#pragma once
#include <DxLib.h>
/*
*	@brief	時間管理クラス
*	@tips シングルトン
*/
class TimeManager
{
#pragma region シングルトンのデータ構造

private:
	static TimeManager* pInstance;
private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	TimeManager();

	/*
	* @brief デストラクタ
	*/
	~TimeManager();

public:		// コピーと譲渡の禁止
	TimeManager(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;

	TimeManager& operator = (const TimeManager&) = delete;
	TimeManager& operator = (TimeManager&&) = delete;


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
	static TimeManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();

#pragma endregion

private:	// メンバ変数
	int prevTime, currentTime;		// 1フレーム前の時間と現在の時間
	float deltaTime;				// フレーム間の経過時間

	int m, s, ms;					// 分、秒、ミリ秒

public:		// メンバ関数

	void Start();

	void Update();

	void Render();


public:		// アクセッサ
	/*
	* @function
	* @brief フレーム間の経過時間を取得
	*/
	inline float GetDeltaTime() const { return deltaTime; }

	inline int GetCurrent() const { return currentTime; }

	inline int GetNow() const { return GetNowCount(); }

};

