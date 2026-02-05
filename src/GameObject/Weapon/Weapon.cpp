#include "Weapon.h"
#include "../../Component/Collider.h"
#include "../../Manager/EffectManager.h"
#include "../../Manager/CollisionManager.h"

/*
* @brief コンストラクタ
*/
Weapon::Weapon(std::string _tag)
	:GameObject(VZero, _tag)
	, modelHandle(INVALID)
	, attachModelHandle(INVALID)
	, attachFrameIndex(INVALID)
	, isAttacking(false)
{
}

/*
* @brief デストラクタ
* @tips		継承して使うときは仮想関数にする。
*/
Weapon::~Weapon()
{
	MV1DeleteModel(modelHandle);
}

/**
* @function		Start
* @brief		初期化処理
* @tips			純粋仮想関数で実装する
*/
void Weapon::Start()
{
}

/**
* @function		Update
* @brief		更新処理
* @tips			純粋仮想関数で実装する
*/
void Weapon::Update()
{
	if (!isVisible) {
		return;
	}


	matrix = MV1GetFrameLocalWorldMatrix(attachModelHandle, attachFrameIndex);

	MV1SetMatrix(modelHandle, matrix);
}
/**
* @function		Render
* @brief		描画処理
* @tips			純粋仮想関数で実装する
*/
void Weapon::Render()
{
	if (!isVisible) {
		return;
	}

	MV1DrawModel(modelHandle);


	if (pCollider != nullptr) {
		pCollider->Render();
	}
	if (pCollider != nullptr) {
		pCollider->Render();
	}
	if (pCollider != nullptr) {
		pCollider->Render();
	}

}

/*
	* @function	Attach
	* @brief	武器を取り付ける、持たせる
	* @param[in]	int&	_attachiModel	持たせるモデルハンドル
	* @param[in]	int&	_weaponModel	武器のモデルハンドル
	* @param[in]	std::string	_frameName	アタッチするフレーム名
	*/
void Weapon::Attach(int& _attachiModel, int& _weaponModel, std::string _frameName)
{

	// 持たせるキャラクタのモデルハンドル
	attachModelHandle = _attachiModel;
	// 武器のモデルハンドル
	modelHandle = _weaponModel;

	// キャラクタの持たせる場所のフレーム番号
	attachFrameIndex = MV1SearchFrame(attachModelHandle, _frameName.c_str());

	matrix = MV1GetFrameLocalWorldMatrix(attachModelHandle, attachFrameIndex);

	// wpMatrix = MV1GetFrameLocalWorldMatrix(attachModelHandle, attachFrameIndex);

	MV1SetMatrix(modelHandle, matrix);
}


void Weapon::OnTriggerEnter(Collider* _pCol) {

	if (_pCol->GetGameObject()->GetTag() == "Goblin") {
		if (!getIsAttacking()) {
			EffectManager::GetInstance()->Instantiate("Hit", VAdd(_pCol->GetGameObject()->GetPosition(), VScale(VUp, 100)));
			setIsAttacking(false);
		}
	}
}

void Weapon::OnTriggerStay(Collider* _pCol)
{
}

void Weapon::OnTriggerExit(Collider* _pCol)
{
}
