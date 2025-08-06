#include "Weapon.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_tag"></param>
Weapon::Weapon(std::string _tag)
	: GameObject(VZero, _tag)
	, modelHandle(INVALID)
	, attachiModelHandle(INVALID)
	, attachiFrameIndex(INVALID)
	, isAttacking(false)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Weapon::~Weapon()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Weapon::Start()
{
}

/// <summary>
/// 更新
/// </summary>
void Weapon::Update()
{
	if (!isVisible) {
		return;
	}
	
	matrix = MV1GetFrameLocalWorldMatrix(attachiModelHandle, attachiFrameIndex);
	MV1SetMatrix(modelHandle, matrix);
}

/// <summary>
/// 描画
/// </summary>
void Weapon::Render()
{
	if (!isVisible) {
		return;
	}

	MV1DrawModel(modelHandle);
}

/// <summary>
/// 武器を持たせる
/// </summary>
/// <param name="_attachiModel">持たせるモデルハンドル</param>
/// <param name="_weaponModel">持たせる武器のハンドル</param>
/// <param name="_frameName">持たせるモデルの持たせるポイント</param>
void Weapon::Attach(int& _attachiModel, int& _weaponModel, std::wstring _frameName)
{
	attachiModelHandle = _attachiModel;
	modelHandle = _weaponModel;

	attachiFrameIndex = MV1SearchFrame(attachiModelHandle, _frameName.c_str());

	matrix = MV1GetFrameLocalWorldMatrix(attachiModelHandle, attachiFrameIndex);

	MV1SetMatrix(modelHandle, matrix);
}
