#pragma once
#include "../GameObject.h"
class Camera : public GameObject
{
private:
	GameObject* pTarget;	// ’Ç]‘ÎÛ‚Ìƒ|ƒCƒ“ƒ^
	float armLength;		// ’Ç]‘ÎÛ‚Æ‚Ì‹——£

	VECTOR offset;			// ˆÊ’u

	VECTOR shakeOffset;		// —h‚ê‚Ì’²®
	VECTOR shakePattern;	// ÀÛ‚Ì—h‚ê
	float timer;			// ŠÔŒv‘ª—p
	float shakeTime;		// —h‚êŠÔ

	bool isShaking;			// —h‚ê’†H

	short LStickX;
	short LStickY;
	short RStickX;
	short RStickY;

	unsigned char LTrigger;
	unsigned char RTrigger;

public:
	static Camera* main;	// ƒƒCƒ“ƒJƒƒ‰

public:
	Camera(VECTOR _pos = VZero, float _length = 500.0f);

	~Camera();

public:
	void Start() override;

	void Update() override;

	void Render() override;

public:
	void Shake(int _direction, float _time, float _power = 0.25f);

	inline GameObject* GetTarget() const { return pTarget; }

	inline void SetTarget(GameObject* _v) { pTarget = _v; }
};

