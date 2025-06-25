#include "InputManager.h"

InputManager* InputManager::pInstance = nullptr;

InputManager::InputManager()
	: xinput()
	, prevxinput()
	, keyState()
	, prevKeyState() {

}

void InputManager::CreateInstance() {
	pInstance = new InputManager();
}

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
	// キーボードの入力を更新
	memcpy_s(prevKeyState, 256, keyState, 256);
	GetHitKeyStateAll(keyState);
	// Xinputコントローラの入力を更新
	prevxinput = xinput;
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
}