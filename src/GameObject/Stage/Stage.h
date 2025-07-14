#pragma once
#include "../GameObject.h"
#include "../../Definition.h"
#include <vector>

class Stage : public GameObject
{
private:
	int modelHandle;								// ステージのモデルハンドル
	std::vector<GameObject*> onGroundObjectArray;	// 接地判定が必要なオブジェクト
public:
	Stage();

	~Stage();

public:
	void Start() override;
	void Update() override;
	void Render() override;

public:
	// 接地オブジェクトとしてインスタンスに登録する。
	void Register(GameObject* _pObj);

public:
	/// <summary>
	/// 地形のモデルハンドルを設定する
	/// </summary>
	/// <param name="_v">ハンドル</param>
	inline void SetModelHandle(int& _v) {
		modelHandle = _v;
	}
};

