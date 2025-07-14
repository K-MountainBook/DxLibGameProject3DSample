#pragma once
#include <DxLib.h>
#include <vector>
#include <string>
/// <summary>
/// アニメーションクリップのクラス（情報を持つだけ）
/// </summary>
class AnimationClip {
public:
	int animationHandle;

	float playTime;
	float totalTime;

	float playSpeed;
	bool isLoop;

	int transtion;
public:
	AnimationClip(int _animHandle, bool _isLoop = false, int _transition = 0)
		:animationHandle(_animHandle),
		playTime(0.0f),
		totalTime(0.0f),
		playSpeed(1.0f),
		isLoop(_isLoop),
		transtion(_transition) {
	}

	~AnimationClip() {
		MV1DeleteModel(animationHandle);
	}

};

/// <summary>
/// アニメーターのクラス
/// </summary>
class Animator
{
private:
	int animationModelHandle;			// アニメーションをさせるモデルのハンドル
	std::vector<AnimationClip*> pAnimations;	// アニメーションクリップの配列
	int currentAnimationHandle;					// 現在再生しているアニメーションのハンドル
	bool isPlaying;								// 再生中フラグ

public:
	Animator();

	~Animator();

public:
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// アニメーションを読み込む
	/// </summary>
	/// <param name="_filePath">ファイルパス</param>
	/// <param name="_isLoop">ループするアニメーションか</param>
	/// <param name="_transition"></param>
	void Load(std::wstring _filePath, bool _isLoop = false, int _transition = 0);

	void Play(int _index, float speed = 1.0f);

public:
	/// <summary>
	/// アニメーションさせるモデルの読み込み
	/// </summary>
	/// <param name="_v">3Dモデルのハンドル</param>
	inline void SetModelHandle(int& _v) {
		animationModelHandle = _v;
	}
	
	/// <summary>
	/// アニメーションクリップの取得
	/// </summary>
	/// <param name="_index">何番目か</param>
	/// <returns>AnimationClipClass</returns>
	inline AnimationClip* GetAnimation(int _index) const {
		return pAnimations[_index];
	}

	/// <summary>
	/// 現在再生しているアニメーションの配列番号を取得
	/// </summary>
	/// <returns></returns>
	inline int GetCurrentAnimation() const {
		return currentAnimationHandle;
	}

	/// <summary>
	/// 再生中フラグ
	/// </summary>
	/// <returns></returns>
	inline bool IsPlaying() const {
		return isPlaying;
	}

};

