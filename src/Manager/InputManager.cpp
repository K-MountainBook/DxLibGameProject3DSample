#include "InputManager.h"
#include <DxLib.h>

//静的メンバ変数の初期化
InputManager* InputManager::pInstance = nullptr;

/*
* @brief コンストラクタ
*/
InputManager::InputManager()
	: keyState()
	, prevKeyState() {
}


/*
* @function	CreateInstance
* @brief	自身のインスタンスを生成する。
* @return	InputManager*
*/
void InputManager::CreateInstance() {
	pInstance = new InputManager();
}


/*
* @function GetInstance
* @brief	自身のインスタンスを取得する唯一の手段
* @return	InputManager*	自身のインスタンスのアドレス
*/
InputManager* InputManager::GetInstance() {
	if (pInstance == nullptr) {
		CreateInstance();
	}

	return pInstance;
}

void InputManager::DestroyInstance() {
	if (pInstance != nullptr) {

		delete pInstance;
		pInstance = nullptr;
	}
}

void InputManager::Update() {
	// 1フレーム前のキーの状態を保存
	memcpy_s(prevKeyState, 256, keyState, 256);
	// 今のフレームのキーの状態を取得
	GetHitKeyStateAll(keyState);

}
