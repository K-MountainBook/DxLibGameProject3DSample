#include "Character.h"

Character::Character(VECTOR _pos, std::string _tag)
	:GameObject(_pos, _tag),
	modelHandle(INVALID),
	pAnimator(new Animator())

{
}

Character::~Character()
{
	delete pAnimator;
	MV1DeleteModel(modelHandle);
}
