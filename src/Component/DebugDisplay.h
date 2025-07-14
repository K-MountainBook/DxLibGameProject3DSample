#pragma once
#ifndef UNIQUE_DEBUGDISPLAY
#define UNIQUE_DEBUGDISPLAY
#include <DxLib.h>

#include "../GameObject/Character/Player/Player.h"

/// <summary>
/// デバッグ表示用クラス（シングルトン）
/// </summary>
class DebugDisplay
{
private:
	Player player;
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
public:
	void Update();
	void Render();

public:
	inline void SetPlayer(Player _v) { player = _v; };
};

#endif