#include "Goblin.h"
#include <cmath>

Goblin::Goblin(VECTOR _pos)
	:Character(_pos, "Goblin")
	, pWeapon(nullptr)
	, wayPoints()
	, index(0)
{
	Start();
}

Goblin::~Goblin()
{

}

void Goblin::Start()
{
	if (!isVisible) {
		return;
	}

	//移動する座標を決定する
	wayPoints.push_back(VGet(-1000.0f, 0.0f, -1000.0f));	// 画面左手前
	wayPoints.push_back(VGet(-1000.0f, 0.0f, 1000.0f));	// 画面左奥
	wayPoints.push_back(VGet(1000.0f, 0.0f, 1000.0f));		// 画面右奥
	wayPoints.push_back(VGet(1000.0f, 0.0f, -1000.0f));	// 画面右手前
}

void Goblin::Update()
{
	if (!isVisible) {
		return;
	}

	// 現在の目的地と現在の座標の差を計算する
	VECTOR tempVec = VSub(wayPoints[index], position);
	// 現在地を保存しておく
	VECTOR beforePos = position;

	if (tempVec.x > 0) {
		// 座標の差がプラスであれば、+方向に移動
		position = VAdd(position, VGet(MOVE_SPEED, 0, 0));
	}
	else if (tempVec.x < 0) {
		// 座標の差がマイナスであれば、-方向に移動
		position = VSub(position, VGet(MOVE_SPEED, 0, 0));
	}

	if (tempVec.z > 0) {
		// 座標の差がプラスであれば、+方向に移動
		position = VAdd(position, VGet(0, 0, MOVE_SPEED));
	}
	else if (tempVec.z < 0) {
		// 座標の差がマイナスであれば、-方向に移動
		position = VSub(position, VGet(0, 0, MOVE_SPEED));
	}

	// 前回座標から移動先座標を引いて移動方向ベクトルを取得する
	VECTOR subPos = VSub(beforePos, position);
	// ベクトルの方向から回転角度を算出する
	rotation.y = Rad2Deg(atan2f(subPos.x, subPos.z));

	// 目的地の場所に応じて切り返しの条件を分ける
	//switch (index)
	//{
	//case 0:
	//	if (position.x <= wayPoints[index].x && position.z <= wayPoints[index].z) {
	//		index++;
	//		index = index % wayPoints.size();
	//	}
	//	break;
	//case 1:
	//	if (position.x <= wayPoints[index].x && position.z >= wayPoints[index].z) {
	//		index++;
	//		index = index % wayPoints.size();
	//	}
	//	break;
	//case 2:
	//	if (position.x >= wayPoints[index].x && position.z >= wayPoints[index].z) {
	//		index++;
	//		index = index % wayPoints.size();
	//	}
	//	break;
	//case 3:
	//	if (position.x >= wayPoints[index].x && position.z <= wayPoints[index].z) {
	//		index++;
	//		index = index % wayPoints.size();
	//	}
	//	break;
	//}

	// 絶対値が1000を超えたら切り返しにしてみる
	if (abs(position.x) >= 1000 && abs(position.z) >= 1000) {
		index++;
		index = index % wayPoints.size();
	}

	pAnimator->Update();

	if (pWeapon != nullptr) {
		pWeapon->Update();
	}

	GameObject::Update();
	MV1SetMatrix(modelHandle, matrix);
}

void Goblin::Render()
{
	if (!isVisible) {
		return;
	}

	MV1DrawModel(modelHandle);

	if (pWeapon != nullptr) {
		pWeapon->Render();
	}
}
