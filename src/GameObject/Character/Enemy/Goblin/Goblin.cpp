#include "Goblin.h"
#include "../../../../Manager/InputManager.h"
#include "../../../../Component/Collider.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos"></param>
Goblin::Goblin(VECTOR _pos) :
	Character(_pos, "Goblin")
	, pWeapon(nullptr)
	, wayPoints()
	, index(0)
{
	Start();
}

Goblin::~Goblin() {

}

/// <summary>
/// 初期化処理
/// </summary>
void Goblin::Start() {
	if (!isVisible) {
		return;
	}

	wayPoints.push_back(VGet(-1000.0f, 50.0f, -1000.0f));
	wayPoints.push_back(VGet(-1000.0f, 50.0f, 1000.0f));
	wayPoints.push_back(VGet(1000.0f, 50.0f, 1000.0f));
	wayPoints.push_back(VGet(1000.0f, 50.0f, -1000.0f));
}

/// <summary>
/// 更新処理
/// </summary>
void Goblin::Update() {

	if (!isVisible) {
		return;
	}

	pAnimator->Update();

	//MV1SetPosition(modelHandle, position);
	//MV1SetRotationXYZ(modelHandle, VScale(rotation, DX_PI_F / 180.0f));
	//MV1SetScale(modelHandle, scale);

	if (pWeapon != nullptr) {
		pWeapon->Update();
	}

	// 行列を求める
	// pCollider->Update();
	GameObject::Update();

	
	MV1SetMatrix(modelHandle, matrix);

}

/// <summary>
/// 描画処理
/// </summary>
void Goblin::Render() {

	if (!isVisible) {
		return;
	}

	//モデルの描写
	MV1DrawModel(modelHandle);

	if (pWeapon != nullptr) {
		pWeapon->Render();
	}

}

