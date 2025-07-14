
#include "Animator.h"
#include "../Definition.h"

/// <summary>
/// コンストラクタ
/// </summary>
Animator::Animator()
	:animationModelHandle(INVALID)
	, pAnimations()
	, currentAnimationHandle(INVALID)
	, isPlaying(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Animator::~Animator()
{
	for (auto anim : pAnimations) {
		delete anim;
	}
	pAnimations.shrink_to_fit();
}

/// <summary>
/// 更新
/// </summary>
void Animator::Update()
{
	// 現在アニメーションが設定されていなければ処理を行わない
	if (currentAnimationHandle == INVALID) {
		return;
	}

	// 現在再生中のアニメーションを読み込み済み配列から取得する
	AnimationClip* pCurrentAnim = GetAnimation(currentAnimationHandle);

	// 取得できなければ処理を行わない
	if (pCurrentAnim == nullptr) {
		return;
	}

	// 再生中のアニメーションに対して、再生時間を加算する。
	pCurrentAnim->playTime += pCurrentAnim->playSpeed;

	// 加算の結果再生総時間を超過した場合、0に戻す
	if (pCurrentAnim->playTime > pCurrentAnim->totalTime) {
		isPlaying = false;
		pCurrentAnim->playTime = 0.0f;
		if (pCurrentAnim->isLoop) {
			isPlaying = true;
		}
		else {
			Play(pCurrentAnim->transtion);
		}
	}
	// 時間を進ませたアニメーションをモデルにセットする
	MV1SetAttachAnimTime(animationModelHandle, 0, pCurrentAnim->playTime);

}

/// <summary>
/// アニメーションの読み込み
/// </summary>
/// <param name="_filePath">アニメーションのファイルパス</param>
/// <param name="_isLoop">アニメーションのループ</param>
/// <param name="_transition"></param>
void Animator::Load(std::wstring _filePath, bool _isLoop, int _transition)
{
	AnimationClip* pAnimClip = new AnimationClip(MV1LoadModel(_filePath.c_str()), _isLoop, _transition);
	pAnimations.push_back(pAnimClip);
}


/// <summary>
/// アニメーションの再生
/// </summary>
/// <param name="_index">読み込んだアニメーションの何番目か</param>
/// <param name="_speed">再生速度（1が標準）</param>
void Animator::Play(int _index, float _speed)
{
	// アニメーションが変更されていない場合は処理を行わない
	if (_index == currentAnimationHandle) {
		return;
	}

	// 読み込んだ何番目のアニメーションかを保存
	currentAnimationHandle = _index;
	// 現在モデルに設定されているアニメーションを破棄
	int result = MV1DetachAnim(animationModelHandle, 0);
	// 現在モデルに設定されているアニメーションの情報の初期化
	pAnimations[_index]->playTime = 0.0f;
	pAnimations[_index]->playSpeed = _speed;
	// pAnimations配列に格納されている読み込んだアニメーションをモデルに設定する。
	int attachiIndex = MV1AttachAnim(animationModelHandle, 0, pAnimations[_index]->animationHandle, FALSE);
	// 設定したアニメーションの再生総時間を取得する
	pAnimations[_index]->totalTime = MV1GetAttachAnimTotalTime(animationModelHandle, attachiIndex);
	// アニメーション再生中フラグをＯＮにする。
	isPlaying = true;
}
