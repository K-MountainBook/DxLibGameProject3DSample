#pragma once

#include <DxLib.h>
#include <string>

// マクロ定義
#define WINDOW_WIDTH_HD			(1280)		// HDサイズ幅
#define WINDOW_HEIGHT_HD		(720)		// HDサイズ高さ
#define WINDOW_WIDTH_FHD		(1920)		// FHDサイズ幅
#define WINDOW_HEIGHT_FHD		(1080)		// FHDサイズ高さ
#define WINDOW_WIDTH_SVGA		(800)		// SVGAサイズ幅
#define WINDOW_HEIGHT_SVGA		(600)		// SVGAサイズ高さ

#define FPS_60					(60)		// FPS

#define PLAYER_MOVEMENT			(5.0f)	//	プレイヤーの移動量
#define PLAYER_BULLET_MAX		(256)	// 弾の最大数
#define PLAYER_BULLET_CIRCLE_SHOT (64 - 1)	// 周回ショットの弾数
#define PLAYER_BULLET_ANIMATION_MAX	(4)	// 弾のアニメーション枚数
#define PLAYER_BULLET_MOVEMENT	(10.0f)

#define ENEMY_BULLET_MAX		(100)
#define	ENEMY_BULLET_ANIMATION_MAX	(4)
#define ENEMY_BULLET_SPEED		(2.0f)
#define ENEMY_MAX				(256)	// 画面上に出てくる敵の最大数
#define ENEMY_SPEED				(3)

#define RAPID_FIRE_COUNT		(3)
#define RAPID_FIRE_COOLDOWN		(10)

#define EXPLOSION_MAX			(255)
#define EXPLOSION_ANIMATION_MAX	(4)

#define ONE_WAY_BULLETS			(1)
#define THREE_WAY_BULLETS		(3)
#define FOUR_WAY_BULLETS		(4)

#define DEGREE_CIRCLE			(360.0f)
#define RADIAN_CIRCLE			(4*DX_PI_F)

//	引数付きマクロ定義
#define Deg2Rad(x) ( x / 180.0f * DX_PI_F )
#define Rad2Deg(x) ( x / DX_PI_F * 180.0f )
#define WaveMoveX(x)  ( cosf(x * 0.1) * 10)

// ワールドベクトル
#define VUp			(VGet(0.0f,1.0f,0.0f))
#define VDown		(VGet(0.0f,-1.0f,0.0f))
#define VRight		(VGet(1.0f,0.0f,0.0f))
#define VLeft		(VGet(-1.0f,0.0f,0.0f))
#define VForward	(VGet(0.0f,0.0f,1.0f))
#define VBack		(VGet(0.0f,0.0f,-1.0f))

// ゼロベクトル
#define VZero		(VGet(0.0f,0.0f,0.0f))		// ゼロベクトル
#define VOne		(VGet(1.0f,1.0f,1.0f))		// 単位ベクトル

#define INVALID					(-1)

// 定数定義
// 色
const unsigned int red = GetColor(255, 0, 0);
const unsigned int green = GetColor(0, 255, 0);
const unsigned int blue = GetColor(0, 0, 255);
const unsigned int magenta = GetColor(255, 0, 255);
const unsigned int cyan = GetColor(0, 255, 255);
const unsigned int yellow = GetColor(255, 255, 0);
const unsigned int white = GetColor(255, 255, 255);
const unsigned int black = GetColor(0, 0, 0);
const unsigned int gray = GetColor(128, 128, 128);

extern const int InputAssign[];
extern struct Input input;

extern int PlayerImage;
extern int PlayerBulletImage;
extern int PlayerBulletAnimation[];

extern int EnemyImage;
extern int EnemySpriteHandle[];
extern int EnemyBulletImage;
extern int EnemyBulletAnimations[];

//	エネミーの弾のアニメーション画像
extern int EnemyBulletAnimations[];

extern int bgm;

extern int se1;
extern int se2;

// プロトタイプ定義
void Init();
void Update();
void CollisionCheck();
void Render();

/// <summary>
/// 入力キー列挙型
/// </summary>
enum MyInput {
	W,
	A,
	S,
	D,

	SPACE,
	Z,

	ESC,

	InputMax,
};

/// <summary>
/// 背景レイヤー列挙型
/// </summary>
enum BackGroundLayer {
	BACK_GROUND_1,
	BACK_GROUND_2,
	BACK_GROUND_3,

	BACK_GROUND_IMAGE_MAX,
};


enum GameSceneType {
	Title,
	InGame,
	Result,

	SceneMax
};

// 列挙定数
enum class SceneType {
	Title,
	Game,
	Clear,
	GameOver,
};

enum Direction {
	DOWN,
	LEFT,
	UP,
	RIGHT,

	DirectionMax
};