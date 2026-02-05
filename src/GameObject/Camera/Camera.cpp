#include "Camera.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/TimeManager.h"

// 静的メンバ宣言
Camera* Camera::main = nullptr;

Camera::Camera(VECTOR _pos, float _length) :
	GameObject(_pos),
	pTarget(nullptr),
	armLength(_length)
	, offset(VScale(VUp, 300))
	, shakeOffset(VZero)
	, timer(0)
	, shakeTime(0)
	, isShaking(false) {
	Start();

	// カメラを複数インスタンス化しないのでここで初期化
	main = this;

}

Camera::~Camera() {

}

void Camera::Start() {

}

void Camera::Update() {

	// 入力管理クラスの取得
	InputManager* input = InputManager::GetInstance();

	VECTOR inputVec = VZero;

	// cameraEulerAngle の操作
	if (input->IsKey(KEY_INPUT_UP)) {
		inputVec = VAdd(inputVec, VUp);
	}
	if (input->IsKey(KEY_INPUT_LEFT)) {
		inputVec = VAdd(inputVec, VLeft);
	}
	if (input->IsKey(KEY_INPUT_RIGHT)) {
		inputVec = VAdd(inputVec, VRight);

	}
	if (input->IsKey(KEY_INPUT_DOWN)) {
		inputVec = VAdd(inputVec, VDown);

	}

	if (VSquareSize(inputVec) >= 0.01f) {
		inputVec = VNorm(inputVec);
	}

	rotation.y += -inputVec.x;
	rotation.x += inputVec.y;

	// 原点中心の半径1の球面上の点
	// XZ平面上の成す角をθ、y方面に成す角をφとすると
	// (sinφ * cosθ　,sinφ　*　sinθ　,　cosφ)
	// Z軸とY軸の座標系が異なっているため入れ替え
	// (sinφ * cosθ　, cosφ , sinφ　*　sinθ　)
	// 座標系が更に違う。右手座標系、左手座標系

	// 中心点が原点で半径1の球面上の点
	// 機能はしてない
	VECTOR sphere = VGet(
		sinf(Deg2Rad(rotation.x)) * sinf(Deg2Rad(rotation.y)),
		cosf(Deg2Rad(rotation.x)),
		sinf(Deg2Rad(rotation.x)) * cosf(Deg2Rad(rotation.y))
	);


	// 座標系や回転、三角関数の相互の関係を組み込んだ最終形態
	sphere = VGet(
		-cosf(Deg2Rad(rotation.x)) * sinf(Deg2Rad(rotation.y)),
		sinf(Deg2Rad(rotation.x)),
		-cosf(Deg2Rad(rotation.x)) * cosf(Deg2Rad(rotation.y))
	);

	// 半径をarmLength倍する。
	sphere = VScale(sphere, armLength);
	// 中心点を追従対象の座標分平行移動
	sphere = VAdd(sphere, pTarget->GetPosition());

	position = sphere;
	if (isShaking) {
		timer += TimeManager::GetInstance()->GetDeltaTime();

		position = VAdd(position, VScale(shakePattern, sinf(timer * FPS)));

		if (timer >= shakeTime) {
			isShaking = false;
			timer = 0.0f;
		}
	}

	GameObject::Update();

	// カメラの位置と回転を設定する
	SetCameraPositionAndAngle(VAdd(position, offset), Deg2Rad(rotation.x), Deg2Rad(rotation.y), Deg2Rad(rotation.z));

	// リスナーの設定を行う
	Set3DSoundListenerPosAndFrontPos_UpVecY(position, VAdd(position, forward));

}

void Camera::Render() {
#if _DEBUG
	DrawFormatString(0, 0, red, "Camera.position : %.2f, %.2f, %.2f,", position.x, position.y, position.z);
	DrawFormatString(0, 20, red, "Camera.rotation : %.2f, %.2f, %.2f,", rotation.x, rotation.y, rotation.z);
#endif
}

void Camera::Shake(int _direction, float _time, float _power)
{
	// 既に揺れていた場合は揺らさない
	//if (!isShaking) {
	//	return;
	//}

	// 各種必要な変数を初期化する
	timer = 0.0f;
	shakeTime = _time;
	isShaking = true;
	shakeOffset = VGet(GetRand(200 - 100), GetRand(200 - 100), GetRand(200 - 100));

	// 揺らす方向に応じてパターンを変更する
	switch (_direction) {
	case 0:
		shakePattern = VGet(shakeOffset.x, 0.0f, 0.0f);
		break;
	case 1:
		shakePattern = VGet(0.0f, shakeOffset.y, 0.0f);
		break;
	case 2:
		shakePattern = VGet(shakeOffset.x, shakeOffset.y, 0.0f);
		break;
	default:
		shakePattern = shakeOffset;
		break;
	}

	shakePattern = VScale(shakePattern, _power);

}
