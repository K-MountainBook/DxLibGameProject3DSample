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
	wayPoints.push_back(VGet(-1000.0f, 50.0f, -1000.0f));	// 画面左手前
	wayPoints.push_back(VGet(-1000.0f, 50.0f, 1000.0f));	// 画面左奥
	wayPoints.push_back(VGet(1000.0f, 50.0f, 1000.0f));		// 画面右奥
	wayPoints.push_back(VGet(1000.0f, 50.0f, -1000.0f));	// 画面右手前
}

void Goblin::Update()
{
	if (!isVisible) {
		return;
	}

	VECTOR tempVec = VSub(wayPoints[index], position);

	if (tempVec.x > 0) {
		position = VAdd(position, VGet(10, 0, 0));
	}
	else if (tempVec.x < 0) {
		position = VSub(position, VGet(10, 0, 0));
	}

	if (tempVec.z > 0) {
		position = VAdd(position, VGet(0, 0, 10));
	}
	else if (tempVec.z < 0) {
		position = VSub(position, VGet(0, 0, 10));
	}


	switch (index)
	{
	case 0:
		if (position.x <= wayPoints[index].x && position.z <= wayPoints[index].z) {
			index++;
			index = index % wayPoints.size();
		}
		break;
	case 1:
		if (position.x <= wayPoints[index].x && position.z >= wayPoints[index].z) {
			index++;
			index = index % wayPoints.size();
		}
		break;
	case 2:
		if (position.x >= wayPoints[index].x && position.z >= wayPoints[index].z) {
			index++;
			index = index % wayPoints.size();
		}
		break;
	case 3:
		if (position.x >= wayPoints[index].x && position.z <= wayPoints[index].z) {
			index++;
			index = index % wayPoints.size();
		}
		break;
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
