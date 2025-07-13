#include <climits>
#include "Player.h"
#include "../../../Manager/InputManager.h"
#include "../../Camera/Camera.h"

Player::Player(VECTOR _pos) :
	Character(_pos, "player")
	, inputX(0)
	, inputY(0)
	, key(0)
{
	Start();
}

Player::~Player()
{
}

void Player::Start()
{
	if (!isVisible) {
		return;
	}

	rotation.y = 180;
}

void Player::Update()
{
	if (!isVisible) {
		return;
	}

	VECTOR inputVec = VZero;
	InputManager* xinput = InputManager::GetInstance();
	short xAxis;
	short yAxis;

	// 現フレームのキー入力状況を取得する
	xinput->GetLeftStick(&xAxis, &yAxis);

	// TODO 移動方向がカメラの方向に影響されるように修正する必要がある
	// 
	// 矢印キーでも、左スティックでも動くように調整
	{
		// 手前
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_DOWN) || yAxis < SHRT_MIN  / 2 || xinput->IsKey(KEY_INPUT_S)) {
			key = 1;
			inputVec = VAdd(inputVec, VBack);
			direction = DOWN;
		}
		// 奥
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_UP) || yAxis > SHRT_MAX / 2 || xinput->IsKey(KEY_INPUT_W)) {
			key = 1;
			inputVec = VAdd(inputVec, VForward);
			direction = UP;
		}
		// 左
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_LEFT) || xAxis < SHRT_MIN / 2 || xinput->IsKey(KEY_INPUT_A)) {
			key = 1;
			inputVec = VAdd(inputVec, VLeft);
			direction = LEFT;
		}
		// 右
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_RIGHT) || xAxis > SHRT_MAX / 2 || xinput->IsKey(KEY_INPUT_D)) {
			key = 1;
			inputVec = VAdd(inputVec, VRight);
			direction = RIGHT;
		}

		// TODO アニメーションの設定
		if (key == 0) {
			if (running == true) {
				running = false;
				// TODO:アニメーションの処理の記述
				pAnimator->Play(0);
			}
		}
		else {
			if (running == false) {
				running = true;
				pAnimator->Play(1, 0.2f);
			}
		}
	}
	// 正規化したベクトルを作成して、移動力を掛けた値を現在の位置に足す。
	// ゼロベクトルを渡すと正規化できないと判断しALL-1.0fを返すのでキー入力があった場合のみ実行
	VECTOR NormVec = VZero;
	VECTOR moveDirection = VZero;
	if (key == 1) {
		NormVec = VNorm(inputVec);
		key = 0;

		// カメラから見た方向に移動する方向ベクトルの変数を作成

		// カメラのy軸回転を取得
		float thetaY = Deg2Rad(Camera::main->GetRotation().y);
		// カメラのY軸回転を元に行列を作成
		MATRIX mRot = MGetRotY(thetaY);

		// 行列をベクトルに変換
		moveDirection = VTransform(inputVec, mRot);

		rotation.y = Rad2Deg(atan2f(moveDirection.x, moveDirection.z));
		position = VAdd(position, VScale(moveDirection, 10.0f));


		// 移動方向に向ける（VGetの引数二つ目のY(0～4の整数を取る)にラジアンの90度*方向を掛ける。）
		// 現在だとキー入力に対した直角しか回転できないので移動方向へ向けるようにする
		// →atanでxとyのベクトルから角度を取得して格納
		MV1SetRotationXYZ(modelHandle, VGet(0.0f, atan2f(moveDirection.x, moveDirection.z) + DX_PI_F, 0.0f));

	}
#if _DEBUG
	printfDx(L"%f\n", rotation.y);
#endif
	// 指定されたハンドルのモデルのポジションを更新する
	MV1SetPosition(modelHandle, position);
}

void Player::Render()
{
	if (!isVisible) {
		return;
	}

	MV1DrawModel(modelHandle);

	DrawFormatString(100, 0, red, L"X:%f, Y:%f, Z:%f", position.x, position.y, position.z);

}
