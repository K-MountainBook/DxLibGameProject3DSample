#include "Camera.h"
#include "../../Manager/InputManager.h"
#include "../../Definition.h"

Camera* Camera::main = nullptr;

Camera::Camera(VECTOR _pos, float _length)
	:GameObject(_pos)
	, pTarget(nullptr)
	, armLength(_length)
	, offset(VScale(VUp, 100))
	, shakeOffset(VZero)
	, timer(0)
	, shakeTime(0)
	, isShaking(false)
	, LStickX()
	, LStickY()
	, RStickX()
	, RStickY()
	, LTrigger()
	, RTrigger()
{
	Start();

	main = this;
}

Camera::~Camera()
{
}

void Camera::Start()
{
}

void Camera::Update()
{
	// inputManagerの情報を読みだすための強引な呼び出し
	// 本来はPlayerクラスで呼び出す
	InputManager* input = InputManager::GetInstance();

	VECTOR inputVec = VZero;

	//input->GetLeftStick(&LStickX, &LStickY);
	//input->GetRightStick(&RStickX, &RStickY);
	input->GetLRStick(&LStickX, &LStickY, &RStickX, &RStickY);
	input->GetLeftTrigger(&LTrigger);
	input->GetRightTrigger(&RTrigger);

	if (RStickY > SHRT_MAX / 2 || input->IsKey(KEY_INPUT_UP)) {
		inputVec = VAdd(inputVec, VUp);
	}
	if (RStickX > SHRT_MAX / 2 || input->IsKey(KEY_INPUT_RIGHT)) {
		inputVec = VAdd(inputVec, VRight);
	}
	if (RStickX < SHRT_MIN / 2 || input->IsKey(KEY_INPUT_LEFT)) {
		inputVec = VAdd(inputVec, VLeft);
	}
	if (RStickY < SHRT_MIN / 2 || input->IsKey(KEY_INPUT_DOWN)) {
		inputVec = VAdd(inputVec, VDown);
	}

	// この書き方だと1フレーム毎に1度(VUp等の値)Degree角が変化する。
	// Y方向に成す角φ
	// →対象を中心にカメラが移動するため、横入力だと上下の回転はせずY座標を中心に回転する
	// 逆時計回り（マイナス方向）
	rotation.y += -inputVec.x;
	// XZ平面上の成す角θ
	// →対象を中心にカメラが移動するため、縦入力だと左右の回転はせずX座標を中心に回転する。
	// とりあえずキーの方向にカメラが動くようにするためプラス方向へ回す
	rotation.x += inputVec.y;

	// オーバーフロー防止
	if (rotation.x <= -360 || rotation.x >= 360) {
		rotation.x = 0;
	}
	if (rotation.y <= -360 || rotation.y >= 360) {
		rotation.y = 0;
	}

	// カメラの角度に合わせて、対象を中心とした球状にカメラを移動させる
	// 半径を1、中心を(0,0,0)とした位置を算出する
	VECTOR sphere = VGet(
		-cosf(Deg2Rad(rotation.x)) * sinf(Deg2Rad(rotation.y)),		
		sinf(Deg2Rad(rotation.x)),									// 2025/07/07 ここがcosfになってただけでした
		-cosf(Deg2Rad(rotation.x)) * cosf(Deg2Rad(rotation.y))		
	);

	// 半径を定数倍して距離を合わせる
	sphere = VScale(sphere, 200.0f);
	// カメラターゲットのポジションを足しこんで位置を調整する
	sphere = VAdd(sphere, pTarget->GetPosition());
	// カメラのポジションを決定する。
	position = sphere;

	GameObject::Update();

	// カメラの位置と回転の設定を行う
	SetCameraPositionAndAngle(
		VAdd(position, offset), Deg2Rad(rotation.x), Deg2Rad(rotation.y), Deg2Rad(rotation.z)
	);
}

void Camera::Render()
{

#if _DEBUG
	DrawFormatString(0, 200, red, L"Camera.position : %.2f, %.2f, %.2f,", position.x, position.y, position.z);
	DrawFormatString(0, 220, red, L"Camera.rotation : %.2f, %.2f, %.2f,", rotation.x, rotation.y, rotation.z);
#endif
	// SetCameraPositionAndTarget_UpVecY(position, pTarget->GetPosition());

}

void Camera::Shake(int _direction, float _time, float _power)
{
}
