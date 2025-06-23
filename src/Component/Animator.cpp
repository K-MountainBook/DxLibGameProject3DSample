
#include "Animator.h"
#include "../Definition.h"

Animator::Animator()
	:animationModelHandle(INVALID)
	, pAnimations()
	, currentAnimationHandle(INVALID)
	, isPlaying(false)
{
}

Animator::~Animator()
{
	for (auto anim : pAnimations) {
		delete anim;
	}
	pAnimations.shrink_to_fit();
}

void Animator::Update()
{
}

void Animator::Load(std::wstring _filePath, bool _isLoop, int _transition)
{
	AnimationClip* pAnimClip = new AnimationClip(MV1LoadModel(_filePath.c_str()), _isLoop, _transition);
	pAnimations.push_back(pAnimClip);
}

void Animator::Play(int _index, float speed)
{
	if (_index == currentAnimationHandle) {
		return;
	}

	currentAnimationHandle = _index;
	MV1DetachAnim(animationModelHandle, 0);
	pAnimations[_index]->playTime = 0.0f;
	pAnimations[_index]->playSpeed = 1.0f;

	int attachiIndex = MV1AttachAnim(animationModelHandle,0, pAnimations[_index]->animationHandle, false);

	pAnimations[_index]->totalTime = MV1GetAttachAnimTotalTime(animationModelHandle, attachiIndex);

	// MV1SetRotationXYZ(model1, VGet(0.0f, DX_PI / 2 * direction, 0.0f));
	// MV1SetPosition(model1, );


	isPlaying = true;
}
