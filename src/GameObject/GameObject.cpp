#include "GameObject.h"

GameObject::GameObject(VECTOR _pos, std::string _tag)
	:isVisble(false)
	, position(VZero)
	, rotaiton(VZero)
	, scale(VZero)
	, matrix(MGetIdent())
	, tag("")
	, forward(VZero)
	, right(VZero)
	, up(VZero)
{
}

GameObject::~GameObject()
{
}
