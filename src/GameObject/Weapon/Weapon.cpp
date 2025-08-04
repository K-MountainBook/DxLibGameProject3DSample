#include "Weapon.h"

Weapon::Weapon(std::string _tag)
	:modelHandle(INVALID)
	,attachiModelHandle(INVALID)
	,attachiFrameIndex(INVALID)
	, isAttacking(false)
{
}

Weapon::~Weapon()
{
	MV1DeleteModel(modelHandle);
}

void Weapon::Start()
{
}

void Weapon::Update()
{
	if (!isVisible) {
		return;
	}

	matrix = MV1GetFrameLocalWorldMatrix(attachiModelHandle, attachiFrameIndex);
	MV1SetMatrix(modelHandle, matrix);
}

void Weapon::Render()
{
	if (!isVisible) {
		return;
	}

	MV1DrawModel(modelHandle);
}

void Weapon::Attach(int& _attachiModel, int& _weaponModel, std::wstring _frameName)
{
	attachiModelHandle = _attachiModel;
	modelHandle = _weaponModel;

	attachiFrameIndex = MV1SearchFrame(attachiModelHandle, _frameName.c_str());

	matrix = MV1GetFrameLocalWorldMatrix(attachiModelHandle, attachiFrameIndex);

	MV1SetMatrix(modelHandle, matrix);
}
