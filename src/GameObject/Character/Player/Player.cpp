#include <climits>
#include "Player.h"
#include "../../../Manager/InputManager.h"

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
	if (!isVisble) {
		return;
	}

	rotation.y = 180;
}

void Player::Update()
{
	if (!isVisble) {
		return;
	}

	VECTOR inputVec = VZero;
	InputManager* xinput = InputManager::GetInstance();
	short xAxis;
	short yAxis;

	xinput->Update();
	xinput->GetLeftStick(&xAxis, &yAxis);

	// 矢印キーでも、左スティックでも動くように調整
	{
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_DOWN) || yAxis < SHRT_MIN  / 2) {
			key = 1;
			inputVec.z -= 4.0f;
			direction = DOWN;
		}
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_UP) || yAxis > SHRT_MAX / 2) {
			key = 1;
			inputVec.z += 4.0f;
			direction = UP;
		}
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_LEFT) || xAxis < SHRT_MIN / 2) {
			key = 1;
			inputVec.x -= 4.0f;
			direction = LEFT;
		}
		if (xinput->IsButton(XINPUT_BUTTON_DPAD_RIGHT) || xAxis > SHRT_MAX / 2) {
			key = 1;
			inputVec.x += 4.0f;
			direction = RIGHT;
		}
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
	if (key == 1) {
		NormVec = VNorm(inputVec);
		key = 0;
	}
	position = VAdd(position, VScale(NormVec, 10.0f));

	// 指定されたハンドルのモデルのポジションを更新する
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, DX_PI / 2 * direction, 0.0f));
	MV1SetPosition(modelHandle, position);
}

void Player::Render()
{
	if (!isVisble) {
		return;
	}

	MV1DrawModel(modelHandle);

	DrawFormatString(100, 0, red, L"X:%f, Y:%f, Z:%f", position.x, position.y, position.z);

}
