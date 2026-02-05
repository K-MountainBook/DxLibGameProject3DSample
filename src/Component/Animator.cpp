#include "Animator.h"
#include "../Definition.h"

/*
* @brief	コンストラクタ
*/
Animator::Animator()
	: animationModelHandle(INVALID)
	, pAnimations()
	, currentAnimation(INVALID)
	, isPlaying(false) {
}


/*
* @brief	デストラクタ
*/
Animator::~Animator() {
	// アニメーション群の解放
	for (auto anim : pAnimations) {
		delete anim;
	}
	pAnimations.shrink_to_fit();
}

/*
* @function	Update
* @brief	更新処理
*/
void Animator::Update() {
	// 無効なアニメーション番号だった場合処理しない
	if (currentAnimation == INVALID) {
		return;
	}

	// 現在のアニメーションを取得する
	AnimationClip* pCurrentAnim = GetAnimation(currentAnimation);

	// NULLチェック
	if (pCurrentAnim == nullptr) {
		return;
	}

	// アニメーションを進める
	pCurrentAnim->playTime += pCurrentAnim->playSpeed;

	// アニメの終了時間を超過したら
	if (pCurrentAnim->playTime > pCurrentAnim->totalTime) {
		// 再生フラグを折る
		isPlaying = false;
		// 再生時間をリセット
		pCurrentAnim->playTime = 0.0f;
		//再生していたアニメーションがループ再生するかどうか
		if (pCurrentAnim->isLoop) {
			// ループするアニメであった場合再生フラグを立てる
			isPlaying = true;
		}
		else {
			//終了時のアニメーションを再生する
			Play(pCurrentAnim->transition);
		}
	}

	MV1SetAttachAnimTime(animationModelHandle, 0, pCurrentAnim->playTime);
}

/*
* @function	Load
* @brief	アニメーションの読み込み
* @param[in]	std::string	filePath		読み込むデータのパス
* @param[in]	bool _isLoop = false		アニメーションをループ再生するかどうか
* @param[in]	int	_transition = 0			終了後の番号
*/
void Animator::Load(std::string _filePath, bool _isLoop, int _transition) {
	// アニメーションの動的確保 + 読み込み
	AnimationClip* pAnimClip = new AnimationClip(MV1LoadModel(_filePath.c_str()), _isLoop, _transition);
	// アニメーション群に追加
	pAnimations.push_back(pAnimClip);
}

/*
* @function Play
* @brief	アニメーションの再生
* @param[in]	int _index
* @param[in]	float _speed
*/
void Animator::Play(int _index, float _speed) {
	if (_index == currentAnimation) {
		return;
	}

	currentAnimation = _index;
	// 再生中だったアニメーションのでタッチ
	MV1DetachAnim(animationModelHandle, 0);
	// 適用するアニメーションの再生時間の初期化
	pAnimations[_index]->playTime = 0.0f;
	// 適用するアニメーションの再生速度の初期化
	pAnimations[_index]->playSpeed = _speed;
	// 適用するアニメーションをアタッチする。
	int attachiIndex = MV1AttachAnim(animationModelHandle, 0, pAnimations[_index]->animationHandle, FALSE);
	// 適用したアニメーションの終了時間を初期化する
	pAnimations[_index]->totalTime = MV1GetAttachAnimTotalTime(animationModelHandle, attachiIndex);
	// 再生中フラグを立てる
	isPlaying = true;


}