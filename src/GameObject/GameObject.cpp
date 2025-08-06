#include "GameObject.h"

GameObject::GameObject(VECTOR _pos, std::string _tag)
	: isVisible(true)
	, position(_pos)
	, rotation(VZero)
	, scale(VOne)
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

/// <summary>
/// 座標、回転、拡縮から行列を作成する
/// </summary>
void GameObject::Update() {
	if (!isVisible) {
		return;
	}

	// 回転行列の作成
	VECTOR theta = VGet(Deg2Rad(rotation.x), Deg2Rad(rotation.y), Deg2Rad(rotation.z));
	MATRIX mRotXYZ = MGetIdent();
	{
		// 座標別に分離して行列を作る
		MATRIX mRotX = MGetRotX(theta.x);
		MATRIX mRotY = MGetRotY(theta.y);
		MATRIX mRotZ = MGetRotZ(theta.z);

		// 行列同士の掛け算をし回転行列を作成する
		mRotXYZ = MMult(MMult(mRotX, mRotY), mRotZ);
	}

	// 拡縮行列の作成
	MATRIX mScale = MGetScale(scale);

	// 平行移動行列
	MATRIX mTranslate = MGetTranslate(position);

	// 回転、拡縮、平行移動行列を掛け合わせてひとつに合成する。
	matrix = MMult(MMult(mRotXYZ, mScale), mTranslate);

}

