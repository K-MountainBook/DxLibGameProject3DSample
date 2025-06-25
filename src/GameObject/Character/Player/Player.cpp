#include "Player.h"

Player::Player(VECTOR _pos) :
	Character(_pos, "player"),
	inputX(0),
	inputY(0),
	key(0),
	xinput()
{
}

Player::~Player()
{
}

void Player::Start()
{
	if (!isVisble) {
		return;
	}
}

void Player::Update()
{
	if (!isVisble) {
		return;
	}

	Direction direction;

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput);
	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

	if (xinput.Buttons[XINPUT_BUTTON_DPAD_DOWN] || inputY > 0) {
		key = 1;
		position.z -= 4.0f;
		direction = DOWN;
	}
	if (xinput.Buttons[XINPUT_BUTTON_DPAD_UP] || inputY < 0) {
		key = 1;
		position.z += 4.0f;
		direction = UP;
	}
	if (xinput.Buttons[XINPUT_BUTTON_DPAD_LEFT] || inputX < 0) {
		key = 1;
		position.x -= 4.0f;
		direction = LEFT;
	}
	if (xinput.Buttons[XINPUT_BUTTON_DPAD_RIGHT] || inputX > 0) {
		key = 1;
		position.x += 4.0f;
		direction = RIGHT;
	}
	if (key == 0) {
		if (running == true) {
			running = false;
			// TODO:アニメーションの処理の記述
		}
	}
	else {
		if (running == false) {
			running = true;
		}
	}



}

void Player::Render()
{
	if (!isVisble) {
		return;
	}

	MV1DrawModel(modelHandle);

}
