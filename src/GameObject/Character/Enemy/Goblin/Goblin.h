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
	Goblin(VECTOR _pos = VZero);

	~Goblin();

public:
	void Start() override;

	void Update() override;

	void Render() override;

public:

	inline Weapon* GetWeapon() const { return pWeapon; }

	inline void SetWeapon(Weapon* _weapon) {
		pWeapon = _weapon;
	}
};

