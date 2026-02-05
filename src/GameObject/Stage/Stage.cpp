#include "Stage.h"
#include "../../Definition.h"

Stage::Stage()
	:GameObject(VZero, "Stage")
	, modelHandle(INVALID)
	, onGroundObjectArray() {
	Start();
}

Stage::~Stage()
{
	MV1DeleteModel(modelHandle);
}

void Stage::Start()
{
}

void Stage::Update()
{
	// レイキャスト->任意の位置から光線を飛ばし、当たったものやポリゴンがあるかどうか調べる
	// モデルに存在するtriangleリスト
	for (int i = 0; i < MV1GetTriangleListNum(modelHandle); i++) {
		// トライアングルリストのポリゴン数繰り返す
		for (int j = 0; j < MV1GetTriangleListPolygonNum(modelHandle, i); j++) {
			VECTOR vertexs[3] = {};
			MV1GetTriangleListPolygonVertexPosition(modelHandle, i, j, vertexs);

			// 位置の変更は対応済み
			vertexs[0] = VAdd(position, vertexs[0]);
			vertexs[1] = VAdd(position, vertexs[1]);
			vertexs[2] = VAdd(position, vertexs[2]);
			// 回転や拡縮の変更に対してはレイキャスト未対応


			// 接地オブジェクト群
			// 接地オブジェクト毎に計算する。
			for (auto pObj : onGroundObjectArray) {
				// 壁
				{
					VECTOR rayOrigin = VAdd(pObj->GetPosition(), VScale(VUp, 120));
					VECTOR rayEnd = VAdd(rayOrigin, VScale(pObj->GetForward(), 30.0f));

					auto hit = HitCheck_Line_Triangle(
						rayOrigin, rayEnd,
						vertexs[0], vertexs[1], vertexs[2]);

					// 当たっていたら壁で止める
					if (hit.HitFlag) {
						pObj->SetPosition(
							hit.Position.x + pObj->GetForward().x * 30,
							pObj->GetPosition().y,
							hit.Position.z + pObj->GetForward().z * 30
						);
						break;
					}
				}
				// 床
				{
					VECTOR rayOrigin = VAdd(pObj->GetPosition(), VScale(VUp, 120));
					VECTOR rayEnd = VAdd(pObj->GetPosition(), VScale(VDown, 150));
					auto hit = HitCheck_Line_Triangle(
						rayOrigin, rayEnd,
						vertexs[0], vertexs[1], vertexs[2]
					);

					// 当たっていたら地面に乗せる
					if (hit.HitFlag) {
						pObj->SetPosition(
							pObj->GetPosition().x,
							hit.Position.y,
							pObj->GetPosition().z
						);
					}
				}
			}
		}
	}
	// 位置、回転、拡縮のセット
	MV1SetPosition(modelHandle, position);
	MV1SetRotationXYZ(modelHandle, VScale(rotation, DX_PI_F / 180.0f));
	MV1SetScale(modelHandle, scale);
}

void Stage::Render()
{
	MV1DrawModel(modelHandle);
}

void Stage::Register(GameObject* _pObj)
{
	onGroundObjectArray.push_back(_pObj);
}
