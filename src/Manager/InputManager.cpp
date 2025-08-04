#include "InputManager.h"
#include "../GameObject/Camera/Camera.h"

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
	memcpy_s(prevKeyState, 256, keyState, 256);
	prevxinput = xinput;
	// キーボードの入力を更新
	GetHitKeyStateAll(keyState);
	// Xinputコントローラの入力を更新
	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
}

void InputManager::DebugRender() {

	DrawFormatString(0, 20, red, L"LeftStickAxisX:%d", xinput.ThumbLX);
	DrawFormatString(0, 40, red, L"LeftStickAxisY:%d", xinput.ThumbLY);
	DrawFormatString(0, 60, red, L"RightStickAxisX:%d", xinput.ThumbRX);
	DrawFormatString(0, 80, red, L"RihgtStickAxisY:%d", xinput.ThumbRY);
	DrawFormatString(0, 100, red, L"LeftTrigger:%d", xinput.LeftTrigger);
	DrawFormatString(0, 120, red, L"RightTrigger:%d", xinput.RightTrigger);

#if _DEBUG
#endif
}