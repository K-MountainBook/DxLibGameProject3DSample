#include "Collider.h"

Collider::Collider(GameObject* _pObj)
	:isEnable(true)
	, pGameObject(_pObj)
	, mat(0)
{
}

Collider::~Collider()
{
}

BoxCollider::BoxCollider(GameObject* _pObj, VECTOR _min, VECTOR _max)
	:Collider(_pObj),
	originMinPoint(_min),
	originMaxPoint(_max),
	originVertex(),
	localVertex(),
	worldVertex() {


	// 回転していない状態での各頂点データを初期化
	originVertex[0] = originMinPoint;												//-100,0,-100
	// Y軸min固定
	originVertex[1] = VGet(originMinPoint.x, originMinPoint.y, originMaxPoint.z);	// -100,0,100
	originVertex[2] = VGet(originMaxPoint.x, originMinPoint.y, originMaxPoint.z);	// 100,0,100
	originVertex[3] = VGet(originMaxPoint.x, originMinPoint.y, originMinPoint.z);	// 100,0,-100
	// Y軸MAX固定
	originVertex[4] = VGet(originMinPoint.x, originMaxPoint.y, originMaxPoint.z);	// -100,100,100
	originVertex[5] = VGet(originMinPoint.x, originMaxPoint.y, originMinPoint.z);	// -100,100,-100
	originVertex[6] = VGet(originMaxPoint.x, originMaxPoint.y, originMinPoint.z);	// 100,100,-100

	originVertex[7] = originMaxPoint;												// 100,200,100
}

/*
* @brief	更新処理
*/
void BoxCollider::Update()
{
	// 無効であった場合は処理しない
	if (!isEnable) {
		return;
	}

	// 拡縮が1では無いモノへの対応
	MATRIX mScale = MGetScale(pGameObject->GetScale());
	// 逆行列というものを取得 ->元の行列と掛け算すると1になる行列
	mScale = MInverse(mScale);

	// Y軸中心の回転行列を取得する
	MATRIX rotY = MMult(mScale, MGetRotY(Deg2Rad(pGameObject->GetRotation().y)));

	// 原点からの平行移動行列を取得する
	MATRIX trans = MGetTranslate(pGameObject->GetPosition());

	// 各頂点分計算
	for (int i = 0; i < 8; i++) {
		// 各頂点のローカルを求める
		// VECTOR * MATRIX -> 回転後のベクトル
		localVertex[i] = VTransform(originVertex[i], rotY);
		localVertex[i] = originVertex[i];

		// 各頂点のワールド座標を求める
		worldVertex[i] = VTransform(localVertex[i], trans);
	}
	// 見た目だけ。当たり判定の計算は開店前のAABBで行う。

}

/*
* @brief	描画処理
*/
void BoxCollider::Render()
{
	if (!isEnable) {
		return;
	}

	// 線分の描画
	// 底辺
	DrawLine3D(worldVertex[0], worldVertex[1], green);
	DrawLine3D(worldVertex[1], worldVertex[2], green);
	DrawLine3D(worldVertex[2], worldVertex[3], green);
	DrawLine3D(worldVertex[3], worldVertex[0], green);

	DrawLine3D(worldVertex[7], worldVertex[4], green);
	DrawLine3D(worldVertex[4], worldVertex[5], green);
	DrawLine3D(worldVertex[5], worldVertex[6], green);
	DrawLine3D(worldVertex[6], worldVertex[7], green);


	DrawLine3D(worldVertex[1], worldVertex[4], green);
	DrawLine3D(worldVertex[2], worldVertex[7], green);
	DrawLine3D(worldVertex[3], worldVertex[6], green);
	DrawLine3D(worldVertex[0], worldVertex[5], green);

}

SphereCollider::SphereCollider(GameObject* _pObj, VECTOR _offset, float _radius)
	:Collider(_pObj)
	, localCenter(_offset)
	, worldCenter(VZero)
	, radius(_radius) {
}

void SphereCollider::Update()
{
	if (!isEnable) {
		return;
	}
	worldCenter = VAdd(pGameObject->GetPosition(), localCenter);
}

void SphereCollider::Render()
{
	if (!isEnable) {
		return;
	}

	DrawSphere3D(worldCenter, radius, 16, green, black, false);

}

CapsuleCollider::CapsuleCollider(GameObject* _pObj, VECTOR _p1, VECTOR _p2, float _radius)
	:Collider(_pObj)
	, originPoint1(_p1)
	, originPoint2(_p2)
	, radius(_radius)
	, offset(VScale(VUp, _radius))
	, localPoint1(VZero)
	, localPoint2(VZero)
	, worldPoint1(VZero)
	, worldPoint2(VZero)
{
	originPoint1 = VAdd(originPoint1, offset);
	originPoint2 = VAdd(originPoint2, offset);
}

/// <summary>
/// 更新処理
/// </summary>
void CapsuleCollider::Update()
{
	// 無効であった場合は処理しない
	if (!isEnable) {
		return;
	}

	MATRIX mat = pGameObject->GetMatrix();

	// 拡縮が1では無いモノへの対応
	MATRIX mScale = MGetScale(pGameObject->GetScale());
	// 逆行列というものを取得 ->元の行列と掛け算すると1になる行列
	mScale = MInverse(mScale);

	// Y軸中心の回転行列を取得する
	// MATRIX rotY = MGetRotY(Deg2Rad(pGameObject->GetRotation().y));
	MATRIX rotXYZ = MMult(mScale, MGetRotElem(mat));

	// 原点からの平行移動行列を取得する
	// MATRIX trans = MGetTranslate(pGameObject->GetPosition());
	// mat.m[3][0];
	VECTOR trans = MGetTranslateElem(mat);

	// 各頂点分計算
	// 各頂点のローカルを求める
	// VECTOR * MATRIX -> 回転後のベクトル
	localPoint1 = VTransform(originPoint1, rotXYZ);
	localPoint2 = VTransform(originPoint2, rotXYZ);

	// 各頂点のワールド座標を求める
	worldPoint1 = VAdd(localPoint1, trans);
	worldPoint2 = VAdd(localPoint2, trans);

	// 見た目だけ。当たり判定の計算は回転前のAABBで行う。

}

void CapsuleCollider::Render()
{
	if (!isEnable) {
		return;
	}
	DrawCapsule3D(worldPoint1, worldPoint2, radius, 16, green, black, FALSE);
}
