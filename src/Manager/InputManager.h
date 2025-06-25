#pragma once
#include <DxLib.h>
/// <summary>
/// 入力管理（シングルトン）
/// </summary>
class InputManager
{
private:
	static InputManager* pInstance;

private:
	InputManager();

	// 暗黙定義されるデフォルトの挙動をする、
	~InputManager() = default;

public:
	// シングルトンを厳密にするためインスタンス化の禁止
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;

	// オペレータオーバーライドで等号によるインスタンスのコピーも禁止
	InputManager& operator = (const InputManager&) = delete;
	InputManager& operator = (InputManager&&) = delete;
private:
	static void CreateInstance();

public:
	static InputManager* GetInstance();
	static void DestroyInstance();

private:
	XINPUT_STATE xinput;
	XINPUT_STATE prevxinput;
	char keyState[256];
	char prevKeyState[256];

public:
	void Update();

public:
	inline bool IsKeyDown(int _key) const {
		return !prevKeyState[_key] && keyState[_key];
	}

	inline bool IsKey(int _key) const {
		return keyState[_key];
	}

	inline bool IsKeyUp(int _key) const {
		return prevKeyState[_key] && !keyState[_key];
	}

	inline bool IsButtonDown(int _key) const {
		return !prevxinput.Buttons[_key] && xinput.Buttons[_key];
	}

	inline bool IsButton(int _key) const {
		return xinput.Buttons[_key];
	}

	inline bool IsButtonUp(int _key) const {
		return prevxinput.Buttons[_key] && !xinput.Buttons[_key];
	}

	void GetLeftStick(short* xAxis, short* yAxis) {
		xAxis = &xinput.ThumbLX;
		yAxis = &xinput.ThumbLY;
	}
};

