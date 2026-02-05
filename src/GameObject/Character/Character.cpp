#include "Character.h"


/*
* @brief	コンストラクタ
* @param[in]	VECTOR _pos = VZero	初期化する座標
*/
Character::Character(VECTOR _pos, std::string _tag)
	: GameObject(_pos, _tag)
	, modelHandle(INVALID)
	, pAnimator(new Animator()) {

}

/*
* @brief	デストラクタ
*/
Character::~Character() {
	// アニメータの解放
	delete pAnimator;
	// モデルハンドルの解放
	MV1DeleteModel(modelHandle);
}
