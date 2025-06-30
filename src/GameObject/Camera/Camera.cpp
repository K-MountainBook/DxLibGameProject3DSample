#include "Camera.h"
#include "../../Manager/InputManager.h"
#include "../../Definition.h"


Camera::Camera(VECTOR _pos, float _length)
	:GameObject(_pos)
	, pTarget(nullptr)
	, armLength(_length)
	, offset(VScale(VUp, 300))
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

	input->Update();
	//input->GetLeftStick(&LStickX, &LStickY);
	//input->GetRightStick(&RStickX, &RStickY);
	input->GetLRStick(&LStickX, &LStickY, &RStickX, &RStickY);
	input->GetLeftTrigger(&LTrigger);
	input->GetRightTrigger(&RTrigger);

	//if (LStickX > 0) {
	//	inputVec = VAdd(inputVec, VRight);
	//}
	//if (LStickX < 0) {
	//	inputVec = VAdd(inputVec, VLeft);
	//}
	//if (LStickY > 0) {
	//	inputVec = VAdd(inputVec, VUp);
	//}
	//if (LStickY < 0) {
	//	inputVec = VAdd(inputVec, VDown);
	//}

	// この書き方だと1フレーム毎に1度(VUp等の値)Degree角が変化する。
	// Y方向に成す角φ
	// →対象を中心にカメラが移動するため、横入力だと上下の回転はせずY座標を中心に回転する
	// rotaiton.y += -inputVec.x;
	// XZ平面上の成す角θ
	// →対象を中心にカメラが移動するため、縦入力だと左右の回転はせずX座標を中心に回転する。
	// rotaiton.x += inputVec.y;

	// カメラの角度に合わせて、対象を中心とした球状にカメラを移動させる

}

void Camera::Render()
{
	DrawFormatString(0, 20, red, L"LeftStickAxisX:%d", LStickX);
	DrawFormatString(0, 40, red, L"LeftStickAxisY:%d", LStickY);
	DrawFormatString(0, 60, red, L"RightStickAxisX:%d", RStickX);
	DrawFormatString(0, 80, red, L"RihgtStickAxisY:%d", RStickY);
	DrawFormatString(0, 100, red, L"LeftTrigger:%d", LTrigger);
	DrawFormatString(0, 120, red, L"RightTrigger:%d", RTrigger);
}

void Camera::Shake(int _direction, float _time, float _power)
{
}
