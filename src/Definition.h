#pragma once
//	=================================================================
//		ヘッダーをインクルードする場所
//	=================================================================
#include <DxLib.h>
#include <string>

//	=================================================================
//		マクロ
//	=================================================================
#define WINDOW_WIDTH			(800)	//	ウィンドウの横幅
#define WINDOW_HEIGHT			(600)	//	ウィンドウの縦幅

#define FPS						(60)	//	FPS

//	引数付きマクロ定義(変換マクロ)
#define Deg2Rad(x)	( x * DX_PI_F / 180.0f )	// デグリー角 -> ラジアン角
#define Rad2Deg(x)	( x * 180.0f / DX_PI_F )	// ラジアン角 -> デグリー角

// ワールドベクトル
#define VRight		(VGet(1.0f,0.0f,0.0f))		// 右
#define VLeft		(VGet(-1.0f,0.0f,0.0f))		// 左
#define VUp			(VGet(0.0f,1.0f,0.0f))		// 上
#define VDown		(VGet(0.0f,-1.0f,0.0f))		// 下
#define VForward	(VGet(0.0f,0.0f,1.0f))		// 前
#define VBack		(VGet(0.0f,0.0f,-1.0f))		// 後

// ゼロベクトル
#define VZero		(VGet(0.0f,0.0f,0.0f))		// ゼロベクトル
#define VOne		(VGet(1.0f,1.0f,1.0f))		// 単位ベクトル

// DxLibの読み込みエラー
#define INVALID		(-1)

// 定数

//	色
const unsigned int red = GetColor(255, 0, 0);
const unsigned int green = GetColor(0, 255, 0);
const unsigned int blue = GetColor(0, 0, 255);
const unsigned int magenta = GetColor(255, 0, 255);
const unsigned int cyan = GetColor(0, 255, 255);
const unsigned int yellow = GetColor(255, 255, 0);
const unsigned int white = GetColor(255, 255, 255);
const unsigned int black = GetColor(0, 0, 0);
const unsigned int gray = GetColor(128, 128, 128);

// 列挙定数
enum class SceneType {
	Title,
	Game,
	Clear,
	GameOver,
};

// フェードの状態
enum class FadeState {
	FadeIn = -1,
	FadeOut = 1,
	FadeEnd,
};