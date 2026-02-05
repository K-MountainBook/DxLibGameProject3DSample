#pragma once
#include "../../Character.h"
#include "../../../Weapon/Weapon.h"


class Goblin : public Character
{
private:
	Weapon* pWeapon;

	std::vector<VECTOR> wayPoints;
	int index;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos"></param>
	Goblin(VECTOR _pos = VZero);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Goblin();

public:	// オーバーライドしたメンバ関数
	/// <summary>
	/// 初期化関数（純粋仮想関数で実装）
	/// </summary>
	void Start() override;

	/// <summary>
	/// 更新関数（純粋仮想関数で実装）
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画関数（純粋仮想関数で実装）
	/// </summary>
	void Render() override;

public:	// メンバ関数

public:	// アクセッサ

	inline Weapon* GetWeapon() const { return pWeapon; }

	inline void SetWeapon(Weapon* weapon) {
		pWeapon = weapon;
	}

};



