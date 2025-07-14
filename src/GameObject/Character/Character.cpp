#include "Character.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="_pos">座標</param>
/// <param name="_tag">タグ</param>
Character::Character(VECTOR _pos, std::string _tag)
	:GameObject(_pos, _tag),
	modelHandle(INVALID),
	pAnimator(new Animator())

{
}

/// <summary>
/// デストラクタ
/// アニメータの削除及び、モデルの破棄
/// </summary>
Character::~Character()
{
	delete pAnimator;
	MV1DeleteModel(modelHandle);
}
