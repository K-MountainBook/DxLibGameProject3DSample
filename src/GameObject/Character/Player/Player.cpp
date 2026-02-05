#include "Player.h"
#include "../../../Manager/InputManager.h"
#include "../../../Component/Collider.h"
#include "../../UI/UIbase.h"

#include "../../Camera/Camera.h"
#include "../../../Manager/EffectManager.h"


// コンストラクタの実体
/*
* @brief	コンストラクタ
* @param[in]	VECTOR _pos = VZero	初期化する座標
*/
Player::Player(VECTOR _pos)
	:Character(_pos, "Player")
	, isAttacking(false)
	, pWeapon(nullptr) {

	Start();
}

Player::~Player() {
	delete pWeapon;
}

/**
* @function		Start
* @brief		初期化処理
*/
void Player::Start() {
	// 非表示だったら初期化しない
	if (!isVisible) {
		return;
	}


	// int uiHandle = LoadGraph("Res/UI/hp.png");

	//HpUi* pUi = new HpUi(this, uiHandle, VAdd(position, VGet(0, 200, 0)), 200, 50);
	//pUi->Render();

	// DrawBillboard3D(VAdd(this->position, VGet(0, 200, 0)), 0.5f, 0.5f, 200, 0, uiHandle, true);

	// Z軸方向を180度回転させる
	rotation.y = 180;
}
/**
* @function		Update
* @brief		更新処理
* @tips			純粋仮想関数で実装する
*/
void Player::Update() {
	if (!isVisible) {
		return;
	}

	InputManager* input = InputManager::GetInstance();

	VECTOR inputVec = VZero;

	// spherePositionを入力によって変更するプログラム
	if (input->IsKey(KEY_INPUT_W)) {
		inputVec = VAdd(inputVec, VForward);
	}
	if (input->IsKey(KEY_INPUT_A)) {
		inputVec = VAdd(inputVec, VLeft);
	}
	if (input->IsKey(KEY_INPUT_S)) {
		inputVec = VAdd(inputVec, VBack);
	}
	if (input->IsKey(KEY_INPUT_D)) {
		inputVec = VAdd(inputVec, VRight);
	}

	if (input->IsKeyDown(KEY_INPUT_SPACE)) {
		isAttacking = true;
		pAnimator->Play(2);
	}

	if (pAnimator->GetCurrentAnimation() != 2) {
		isAttacking = false;
		pWeapon->setIsAttacking(false);
	}



	// 攻撃中でなければ
	if (!isAttacking) {
		// 入力があれば
		if (VSquareSize(inputVec) >= 0.01f) {
			// 入力ベクトルの正規化
			inputVec = VNorm(inputVec);


			// カメラからみた移動する方向ベクトル
			VECTOR moveDirection = VZero;

#if 0	// 三角関数で計算する場合

			// xz平面の回転として考える -> 2次元の回転として扱える
			// 回転後の座標をx'z'、回転する前の座標x zとしたとき
			// x' = x * cosθ - z * sinθ
			// z' = x * sinθ + z * cosθ
			// θ = カメラのy軸回転 -> camera.rotation.y

			float theta = Deg2Rad(Camera::main->GetRotation().y);

			// 座標系の違いからX,Zの値を入れ替える
			float Z = inputVec.z * cosf(theta) - inputVec.x * sinf(theta);
			float X = inputVec.z * sinf(theta) + inputVec.x * cosf(theta);

			// 移動方向を計算結果で初期化
			moveDirection = VGet(X, 0, Z);

			//{
			//	// XZ平面の原点から見た傾き（tanθ）を求める
			//	float tanTheta = X / Z;
			//	// tanθからθのみを求めたい -> （逆三角関数）atanを使う。
			//	atan(tanTheta);
			//}
			// 上のブロックを一発で出す関数
			// Rad2Deg(atan2f(X, Z));

			// 自身のy軸回転を計算した値に変更する。
			rotation.y = Rad2Deg(atan2f(X, Z)) + 180.0f;


#else	// 行列で計算する場合

			// DxLibにて行列用の型がある。MATRIX型
			// 4行4列で全ての値がfloat型
			// カメラの軸回転を行列で取りたい
			// カメラの回転行列を取得する
			//float thetaX = Deg2Rad(Camera::main->GetRotation().x);
			float thetaY = Deg2Rad(Camera::main->GetRotation().y);
			//float thetaZ = Deg2Rad(Camera::main->GetRotation().z);

			//MATRIX mRotX = MGetRotX(thetaX);	// カメラのX軸回転行列
			MATRIX mRotY = MGetRotY(thetaY);	// カメラのX軸回転行列
			//MATRIX mRotZ = MGetRotZ(thetaZ);	// カメラのX軸回転行列

			//// 何かと掛け算としても値が変更されないのが「単位行列」

			//// X>Y>Zの順で回転行列を作成する
			//MATRIX mRotXYZ = MMult(MMult(mRotX, mRotY), mRotZ);

			//// 拡縮行列
			//MATRIX mScale = MGetScale(scale);

			//// 平行移動行列
			//MATRIX mTranslate = MGetTranslate(position);

			//// 行列の乗算は合成できる
			//// 回転行列 -> 拡縮行列 ->平行移動行列の順番でかけ合わせる
			//matrix = MMult(MMult(mRotXYZ, mScale), mTranslate);
			// これがunityやゲームプログラミングで使用される4x4の行列

			// 移動方向を計算結果で初期化
			moveDirection = VTransform(inputVec, mRotY);


			rotation.y = Rad2Deg(atan2f(moveDirection.x, moveDirection.z)) + 180.0f;

#endif


			// 計算した入力ベクトルを加算する
			//	position = VAdd(position, VScale(inputVec, 10.0f));
			// 計算した移動方向ベクトルを加算する
			position = VAdd(position, VScale(moveDirection, 10.0f));

			// 移動するアニメーション再生
			pAnimator->Play(1, 0.2f);
		}
		else {
			pAnimator->Play(0);
		}
	}
	pAnimator->Update();

	GameObject::Update();
	MV1SetMatrix(modelHandle, matrix);

	if (pWeapon != nullptr) {
		pWeapon->Update();
	}


}
/**
* @function		Render
* @brief		描画処理
* @tips			純粋仮想関数で実装する
*/
void Player::Render() {
	if (!isVisible) {
		return;
	}

	// モデルの描画
	MV1DrawModel(modelHandle);
	// 武器の描画
	if (pWeapon != nullptr) {
		pWeapon->Render();
	}

	VECTOR UIPosition = VAdd(position, VGet(-100, -200, 0));

	DrawBox(UIPosition.x, UIPosition.y, UIPosition.x + 200, UIPosition.y + 100, green, true);

}

void Player::OnTriggerEnter(Collider* _pCol) {
	if (_pCol->GetGameObject()->GetTag() == "Goblin") {
		// _pCol->GetGameObject()->SetVisible(false);
		Camera::main->Shake(2, 0.5f);
		EffectManager::GetInstance()->Instantiate("BossDeath", position);
	}
}

void Player::OnTriggerStay(Collider* _pCol) {
}

void Player::OnTriggerExit(Collider* _pCol) {

}
