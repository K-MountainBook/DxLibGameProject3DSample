#pragma once
#include "../../Character.h"
#include "../../../Weapon/Weapon.h"

#define MOVE_SPEED (5)

/// <summary>
/// ゴブリンクラス
/// </summary>
class Goblin : public Character
{
private:
	Weapon* pWeapon;				// 武器を持たせるためのクラス

	std::vector<VECTOR> wayPoints;	// 座標を持たせる配列
	int index;						// 上記のindex

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">座標</param>
	Goblin(VECTOR _pos = VZero);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goblin();

public:
	void Start() override;

	void Update() override;

	void Render() override;

public:

	/// <summary>
	/// 武器を取得する
	/// </summary>
	/// <returns>武器クラス</returns>
	inline Weapon* GetWeapon() const { return pWeapon; }

	/// <summary>
	/// 武器を持たせる
	/// </summary>
	/// <param name="_weapon"></param>
	inline void SetWeapon(Weapon* _weapon) {
		pWeapon = _weapon;
	}
};

