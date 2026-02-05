#pragma once

/*
 * @brief 入力管理クラス
 * @tips 管理するクラスは1つであるべき -> シングルトンのデータ構造
 */
class InputManager {
#pragma ragion シングルトンのデータ構造
private:
	static InputManager* pInstance;

private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	InputManager();

	/*
	* @brief デストラクタ
	*/
	~InputManager() = default;

public:		// コピーと譲渡の禁止
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;

	InputManager& operator = (const InputManager&) = delete;
	InputManager& operator = (InputManager&&) = delete;

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
	static InputManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();


#pragma endregion


private:	// メンバ変数
	char keyState[256];			// 現在のキーの状態
	char prevKeyState[256];		// 1フレーム前のキーの状態
	
public:		// メンバ関数
	/*
	* @function Update
	* @brief	更新処理
	*/
	void Update();

public:		// キーボード用入力管理
	/*
	* @function IsKeyDown
	* @brief	キーが押されたかどうか
	* @param[in] int _key	キー番号
	* @return	bool
	* @tips		押されていない状態 -> 押された状態
	*/
	inline bool IsKeyDown(int _key) const {
		// !前 && 今
		return !prevKeyState[_key] && keyState[_key];
	}

	/*
	* @function IsKey
	* @brief	キーが押しているかどうか
	* @param[in] int _key	キー番号
	* @return	bool
	* @tips		押している状態
	*/
	inline bool IsKey(int _key) const {
		// 今
		return keyState[_key];
	}


	/*
	* @function IsKeyDown
	* @brief	キーが押されたかどうか
	* @param[in] int _key	キー番号
	* @return	bool
	* @tips		押された -> 押されていない状態
	*/
	inline bool IsKeyUp(int _key) const {
		// 前 && !今
		return prevKeyState[_key] && !keyState[_key];
	}

};

