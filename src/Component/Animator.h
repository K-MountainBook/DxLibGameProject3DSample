#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

/*
* @brief アニメーションクリップ構造体
*/
struct AnimationClip {

	int animationHandle;			// アニメーションハンドル

	float playTime;				// アニメーションの再生時間
	float totalTime;			// アニメーションの終了時間

	float playSpeed;			// アニメーションの再生速度
	bool isLoop;				// ループ再生するか

	int transition;				// アニメーションが終了した後に再生する番号

	/*
	* @brief コンストラクタ
	* @param[out]	int	_animationHandle	アニメーションハンドル
	* @param[in]	bool	_isLoop = false		ループ再生するかどうか
	* @param[in]	int		_transition			終了後の番号
	*/
	AnimationClip(int _animHandle, bool _isLoop = false, int _transition = 0)
		: animationHandle(_animHandle)
		, playTime(0.0f)
		, totalTime(0.0f)
		, playSpeed(1.0f)
		, isLoop(_isLoop)
		, transition(_transition) {
	}

	/*
	* @bried	デストラクタ
	*/
	~AnimationClip() {
		MV1DeleteModel(animationHandle);
	}

};

/*
* @brief	アニメーションを管理するクラス
* @tips		アニメーション毎にファイルが分かれているモデル用
*			DxModelViewerを使用してアニメーションの追加読み込みを行っても1つのモデルに
*			複数のアニメーションを保持することはできない
*			=>BlenderやMayaなどの3Dモデルソフトを利用すると可能ではある
*
*			今回は、モデルデータだけ　と　アニメーションデータだけ　の2つを作る必要があり。
*			アニメーションさせる毎にアタッチとでタッチを繰り返す。
*			1つのモデルデータの中に複数のアニメーションがアタッチされている場合は、
*			No.xx　AttachiIndexを切り替えてあげれば勝手に動く
*/
class Animator
{
private:	//メンバ変数
	int animationModelHandle;		// アニメーションを適用する"モデル"のハンドル
	std::vector<AnimationClip*> pAnimations;	// "アニメーション"ハンドル群
	int currentAnimation;						// 現在のアニメーション
	bool isPlaying;								// 再生中かどうか

public:
	/*
	* @brief	コンストラクタ
	*/
	Animator();

	/*
	* @brief	デストラクタ
	*/
	~Animator();

public:			// メンバ関数
	/*
	* @function	Update
	* @brief	更新処理
	*/
	void Update();

	/*
	* @function	Load
	* @brief	アニメーションの読み込み
	* @param[in]	std::string	filePath		読み込むデータのパス
	* @param[in]	bool _isLoop = false		アニメーションをループ再生するかどうか
	* @param[in]	int	_transition = 0			終了後の番号
	*/

	void Load(std::string _filePath, bool _isLoop = false, int _transition = 0);

	/*
	* @function Play
	* @brief	アニメーションの再生
	* @param[in]	int _index
	* @param[in]	float _speed
	*/
	void Play(int _index, float _speed = 1.0f);

public:		// GetterとSetter
	/*
	* @function		SetModelHandle
	* @brief		アニメーションを適用するモデルハンドルをセット
	* @param[out]	int& _v
	*/
	inline void SetModelHandle(int& _v) { animationModelHandle = _v; }

	/*
	* @function		GetAnimation
	* @brief		アニメーションクリップの取得
	* @param[in]	int	_index			取得するアニメーション番号
	* @return		AnimationClip*
	*/
	inline AnimationClip* GetAnimation(int _index) const { return pAnimations[_index]; }

	/*
	* @function	GetCurrentAnimation
	* @brief	現在のアニメーションの取得
	* @return	int
	*/
	inline int GetCurrentAnimation() const { return currentAnimation; }

	/*
	* @function	IsPlaying
	* @brief	アニメーションが再生中かどうか
	* @return	bool
	*/
	inline bool IsPlaying() const { return isPlaying; }

};

