#pragma once
#include <DxLib.h>
#include <vector>
#include <string>

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

class Animator
{
private:
	int animationModelHandle;
	std::vector<AnimationClip*> pAnimations;
	int currentAnimationHandle;
	bool isPlaying;

public:
	Animator();

	~Animator();

public:
	void Update();

	void Load(std::wstring _filePath, bool _isLoop = false, int _transition = 0);

	void Play(int _index, float speed = 1.0f);

public:

	inline void SetModelHandle(int& _v) {
		animationModelHandle = _v;
	}

	inline AnimationClip* GetAnimation(int _index) const {
		return pAnimations[_index];
	}

	inline int GetCurrentAnimation() const {
		return currentAnimationHandle;
	}

	inline bool IsPlaying() const {
		return isPlaying;
	}

};

