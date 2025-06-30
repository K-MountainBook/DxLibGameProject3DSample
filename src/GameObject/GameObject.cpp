#include "GameObject.h"

GameObject::GameObject(VECTOR _pos, std::string _tag)
	:isVisble(true)
	, position(VZero)
	, rotation(VZero)
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

void GameObject::Update() {
	if (!isVisble) {
		return;
	}

}

