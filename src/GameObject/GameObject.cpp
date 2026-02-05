#include "GameObject.h"
#include "../Component/Collider.h"

/*
* @brief	コンストラクタ
* @param[in]	VECTOR _pos = V_Zero	初期化する座標
*/
GameObject::GameObject(VECTOR _pos, std::string _tag)
	: isVisible(true)
	, position(_pos)
	, rotation(VZero)
	, scale(VOne)
	, matrix(MGetIdent())
	, pCollider(nullptr)
	, tag(_tag)
	, forward(VZero)
	, right(VZero)
	, up(VZero) {


}

/*
* @brief	デストラクタ
* @tips		基底クラスなので仮想関数で実装する
*/
GameObject::~GameObject() {
	if (pCollider != nullptr) {
		delete pCollider;
		pCollider = nullptr;
	}
}
/**
* @function		Update
* @brief		更新処理
*/
void GameObject::Update()
{
	if (!isVisible) {
		return;
	}

	// 座標、回転、拡縮から行列を求める
	float thetaX = Deg2Rad(rotation.x);
	float thetaY = Deg2Rad(rotation.y);
	float thetaZ = Deg2Rad(rotation.z);

	MATRIX mRotX = MGetRotX(thetaX);	// 自身のX軸回転行列
	MATRIX mRotY = MGetRotY(thetaY);	// 自身のY軸回転行列
	MATRIX mRotZ = MGetRotZ(thetaZ);	// 自身のZ軸回転行列

	// 何かと掛け算としても値が変更されないのが「単位行列」

	// X>Y>Zの順で回転行列を作成する
	MATRIX mRotXYZ = MMult(MMult(mRotX, mRotY), mRotZ);

	// 拡縮行列
	MATRIX mScale = MGetScale(scale);

	// 平行移動行列
	MATRIX mTranslate = MGetTranslate(position);

	// 行列の乗算は合成できる
	// 回転行列 -> 拡縮行列 ->平行移動行列の順番でかけ合わせる
	matrix = MMult(MMult(mRotXYZ, mScale), mTranslate);


	VECTOR tmp = VTransform(VForward, mRotXYZ);
	if (VSquareSize(tmp) >= 0.01f) {
		forward = VNorm(tmp);
	}
	if (VSquareSize(tmp) >= 0.01f) {
		right = VNorm(tmp);
	}
	if (VSquareSize(tmp) >= 0.01f) {
		up = VNorm(tmp);
	}

	if (pCollider != nullptr) {
		pCollider->SetMatrix(matrix);
	}


}

void GameObject::OnTriggerEnter(Collider* _pOther)
{
}

void GameObject::OnTriggerStay(Collider* _pOther)
{
}

void GameObject::OnTriggerExit(Collider* _pOther)
{
}
