#pragma once
#ifndef UNIQUE_DEBUGDISPLAY
#define UNIQUE_DEBUGDISPLAY
#include <DxLib.h>

#include "../GameObject/Character/Player/Player.h"
#include "../GameObject/Camera/Camera.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

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
	SceneManager* scene;

	
public:
	// プロトタイプ宣言
	void Update();
	void Render();

public:

	/// <summary>
	/// デバッグ表示を行うプレイヤー情報を格納
	/// </summary>
	/// <param name="_v"></param>
	inline void SetPlayer(Player* _v) { player = _v; };

	/// <summary>
	/// デバッグ表示を行うカメラ情報を格納
	/// </summary>
	/// <param name="_v"></param>
	inline void SetCameraInfo(Camera* _v) { camera = _v; }

	/// <summary>
	/// デバッグ表示を行う入力管理情報を格納
	/// </summary>
	/// <param name="_v"></param>
	inline void SetInputManager(InputManager* _v) { input = _v; }

	/// <summary>
	/// デバッグ表示を行うシーン管理情報を格納
	/// </summary>
	/// <param name="_v"></param>
	inline void SetSceneManager(SceneManager* _v) { scene = _v; }
};

#endif