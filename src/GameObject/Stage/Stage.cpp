#include "Stage.h"

Stage::Stage()
	:GameObject(VZero,"Stage")
	, modelHandle(INVALID)
	, onGroundObjectArray()
{
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
	// トライアングルリストとはなんぞや
	// →モデルビューアで確認できるメッシュの塊（テクスチャが同じメッシュ？）
	for (int i = 0; i < MV1GetTriangleListNum(modelHandle); i++) {
		for (int j = 0; j < MV1GetTriangleListPolygonNum(modelHandle, i); j++) {
			VECTOR vertexs[3] = {};
			MV1GetTriangleListPolygonVertexPosition(modelHandle, i, j, vertexs);

			// positionに頂点座標を足したものを作る
			vertexs[0] = VAdd(position, vertexs[0]);
			vertexs[1] = VAdd(position, vertexs[1]);
			vertexs[2] = VAdd(position, vertexs[2]);

			// 登録された接地オブジェクト
			for(auto pObj:onGroundObjectArray){
			// 接地判定
				VECTOR rayOrigin = VAdd(pObj->GetPosition(), VScale(VUp, 120));
				VECTOR rayEnd = VAdd(pObj->GetPosition(), VScale(VDown, 150));
				// rayOrigin→rayEndの線がvertexsの3点が形成する三角にHITするかの確認
				auto hit = HitCheck_Line_Triangle(
					rayOrigin, rayEnd,
					vertexs[0], vertexs[1], vertexs[2]);

				// HitFlagがtrueであった場合登録された接地オブジェクトのy軸を
				// hitした位置（接地位置）の値に入れ替える
				if (hit.HitFlag) {
					pObj->SetPosition(pObj->GetPosition().x, hit.Position.y, pObj->GetPosition().z);
				}
			}
		}
	}
#if 0
	int sum = 0;
	for (int i = 0; i < MV1GetTriangleListNum(modelHandle); i++) {
		// これで対象モデルのポリゴンの合計数が計算できる
		sum += MV1GetTriangleListPolygonNum(modelHandle, i);
	}
	printfDx(L"%d\n", sum);
#endif
}

void Stage::Render()
{
	MV1DrawModel(modelHandle);
}

void Stage::Register(GameObject* _pObj)
{
	// VECTOR型の変数に地形の影響を受けるオブジェクトを登録する
	onGroundObjectArray.push_back(_pObj);
}
