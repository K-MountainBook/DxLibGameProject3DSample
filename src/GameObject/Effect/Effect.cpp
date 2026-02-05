#include "Effect.h"
#include <EffekseerForDXLib.h>

Effect::Effect(int& _resourceHandle)
	: GameObject()
	, resourceHandle(_resourceHandle)
	, playingHandle(INVALID) {

}

Effect::~Effect() {
	StopEffekseer3DEffect(playingHandle);
}

void Effect::Start() {

}
/// <summary>
/// 更新処理
/// </summary>
void Effect::Update() {
	if (!isVisible) {
		return;
	}

	// 再生が終わったら非表示にする
	if (!IsEffekseer3DEffectPlaying(playingHandle)) {
		isVisible = false;
	}

	// エフェクトの再生
	playingHandle = PlayEffekseer3DEffect(resourceHandle);

	// エフェクトの座標の変更
	SetPosPlayingEffekseer3DEffect(playingHandle, position.x, position.y, position.z);

}

/// <summary>
/// 描画処理
/// </summary>
void Effect::Render() {
	if (!isVisible) {
		return;
	}
}