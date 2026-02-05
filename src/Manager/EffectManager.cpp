#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "../GameObject/Effect/Effect.h"

// 静的メンバ変数の初期化
EffectManager* EffectManager::pInstance = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
	: effectResourceMap()
	, pEffectList()
{
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	for (auto itr : effectResourceMap) {
		DeleteEffekseerEffect(itr.second);
	}
	effectResourceMap.clear();

	for (auto pEffe : pEffectList) {
		if (pEffe != nullptr) {
			delete pEffe;
			pEffe = nullptr;
		}
	}
	pEffectList.clear();
}

/// <summary>
/// インスタンス作成
/// </summary>
void EffectManager::CreateInstance() {
	pInstance = new EffectManager();
}

/// <summary>
/// インスタンスの取得
/// </summary>
/// <returns></returns>
EffectManager* EffectManager::GetInstance() {
	if (pInstance == nullptr) {
		CreateInstance();
	}
	return pInstance;
}

/// <summary>
/// インスタンスの破棄
/// </summary>
void EffectManager::DestroyInstance() {
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

/// <summary>
/// エフェクトのロード
/// </summary>
/// <param name="_filePath"></param>
/// <param name="_name"></param>
/// <param name="_magnification"></param>
void EffectManager::Load(std::string _filePath, std::string _name, float _magnification)
{
	int res = LoadEffekseerEffect(_filePath.c_str(), _magnification);
#if 0
	effectResourceMap[_filePath.c_str()] = res;
#else
	// 連想配列の中にすでに登録されているファイルか検索する。
	auto itr = effectResourceMap.find(_name.c_str());
	// 登録されていなければ登録する
	// マップが最後まで来ているということは検索しても無かった
	if (itr == effectResourceMap.end()) {
		// 登録
		effectResourceMap.emplace(_name.c_str(), res);
	}

#endif
}

/// <summary>
/// エフェクトの発生処理
/// </summary>
/// <param name="_name"></param>
/// <param name="_pos"></param>
/// <returns></returns>
Effect* EffectManager::Instantiate(std::string _name, VECTOR _pos)
{
	Effect* pEffect = new Effect(effectResourceMap[_name]);
	pEffect->SetPosition(_pos);
	pEffectList.push_back(pEffect);
	return pEffect;
}

/// <summary>
/// 更新処理
/// </summary>
void EffectManager::Update()
{
	for (auto pEffe : pEffectList) {
		if (pEffe == nullptr || !pEffe->IsVisible()) {
			continue;
		}

		pEffe->Update();

	}

	// STLの要素を削除（条件付き）
	// std::erase_if(コンテナ,イテレータ) C++20
	std::erase_if(
		pEffectList,
		[](Effect* _pEffect) { return !_pEffect->IsVisible(); }
	);

	UpdateEffekseer3D();

}

void EffectManager::Render()
{
	for (auto pEffe : pEffectList) {
		if (pEffe == nullptr || !pEffe->IsVisible()) {
			continue;
		}
		pEffe->Render();
	}
	DrawEffekseer3D();
}
