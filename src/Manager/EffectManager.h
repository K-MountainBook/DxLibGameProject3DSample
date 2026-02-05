#pragma once
#include <map>
#include <string>
#include <list>
#include <DxLib.h>
class EffectManager
{
#pragma region singuruton
private:
	static EffectManager* pInstance;

private:
	EffectManager();

	~EffectManager();
public:		// コピーと譲渡の禁止
	EffectManager(const EffectManager&) = delete;
	EffectManager(EffectManager&&) = delete;

	EffectManager& operator = (const EffectManager&) = delete;
	EffectManager& operator = (EffectManager&&) = delete;

private:
	static void CreateInstance();

public:
	static EffectManager* GetInstance();
	static void DestroyInstance();


#pragma endregion

private:	// 静的メンバ

	std::map<std::string, int> effectResourceMap;
	std::list<class Effect*> pEffectList;

public:
	/// <summary>
	/// エフェクトの読み込み
	/// </summary>
	/// <param name="_filePath"></param>
	/// <param name="_name"></param>
	/// <param name="_magnification"></param>
	void Load(std::string _filePath, std::string _name, float _magnification = 1.0f);

	/// <summary>
	/// エフェクトの発生
	/// </summary>
	class Effect* Instantiate(std::string _name, VECTOR _pos);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Render();


};

