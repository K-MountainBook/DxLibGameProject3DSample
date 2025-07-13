#include "GameObject.h"

GameObject::GameObject(VECTOR _pos, std::string _tag)
	:isVisible(true)
	, position(VZero)
	, rotation(VZero)
	, scale(VZero)
	, matrix(MGetIdent())
	, tag(_tag)
	, forward(VZero)
	, right(VZero)
	, up(VZero)
{
}

GameObject::~GameObject()
{
}

// TODO ゲームオブジェクト全体の移動処理、回転処理を記載する
void GameObject::Update() {
	if (!isVisible) {
		return;
	}

	// 座標、回転、拡縮から行列を作成する
	VECTOR theta = VGet(Deg2Rad(rotation.x), Deg2Rad(rotation.y), Deg2Rad(rotation.z));

	MATRIX mRotX = MGetRotX(theta.x);
	MATRIX mRotY = MGetRotY(theta.y);
	MATRIX mRotZ = MGetRotZ(theta.z);

	// 行列同士の掛け算をし回転行列を作成する
	MATRIX mRotXYZ = MMult(MMult(mRotX, mRotY), mRotZ);

	// 拡縮行列の作成
	MATRIX mScale = MGetScale(scale);

	// 平行移動行列
	MATRIX mTranslate = MGetTranslate(position);

	// 回転、拡縮、平行移動行列を掛け合わせてひとつに合成する。
	matrix = MMult(MMult(mRotXYZ, mScale), mTranslate);

}

