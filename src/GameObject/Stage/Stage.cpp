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
	// TODO トライアングルリストとはなんぞや
	for (int i = 0; i < MV1GetTriangleListNum(modelHandle); i++) {
		for (int j = 0; j < MV1GetTriangleListPolygonNum(modelHandle, i); j++) {
			VECTOR vertexs[3] = {};
			MV1GetTriangleListPolygonVertexPosition(modelHandle, i, j, vertexs);
		}
	}

#if _DEBUG
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
	onGroundObjectArray.push_back(_pObj);
}
