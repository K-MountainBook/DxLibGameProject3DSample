#pragma once
#ifndef UNIQUE_DEBUGDISPLAY
#define UNIQUE_DEBUGDISPLAY
#include <DxLib.h>

#include "../GameObject/Character/Player/Player.h"
#include "../GameObject/Camera/Camera.h"
#include "../Manager/InputManager.h"

/// <summary>
/// デバッグ表示用クラス（シングルトン）
/// </summary>
class DebugDisplay
{
private:
	static DebugDisplay* pInstance;
private:
	DebugDisplay();

	~DebugDisplay() = default;
public:
	DebugDisplay(const DebugDisplay&) = delete;
	DebugDisplay(DebugDisplay&&) = delete;

	DebugDisplay& operator = (const DebugDisplay&) = delete;
	DebugDisplay& operator = (DebugDisplay&&) = delete;
private:
	static void CreateInstance();

public:
	static DebugDisplay* GetInstance();

	static void DestroyInstance();

private:
	// メンバ変数
	Player* player;
	Camera* camera;
	InputManager* input;
public:
	void Update();
	void Render();

public:
	inline void SetPlayer(Player* _v) { player = _v; };

	inline void SetCameraInfo(Camera* _v) { camera = _v; }

	inline void SetInputManager(InputManager* _v) { input = _v; }
};

#endif