#include "CollisionManager.h"
#include "../Component/Collider.h"


CollisionManager* CollisionManager::pInstance = nullptr;

CollisionManager::CollisionManager()
	:pColliderArray()
	, prevs()
	, currents()
	, index(0)
{
}

CollisionManager::~CollisionManager()
{
	//for (auto pCol : pColliderArray) {
	//	if (pCol != nullptr) {
	//		delete pCol;
	//		pCol = nullptr;
	//	}
	//}

	pColliderArray.clear();
	pColliderArray.shrink_to_fit();
	prevs.clear();
	prevs.shrink_to_fit();
	currents.clear();
	currents.shrink_to_fit();

}

void CollisionManager::CreateInstance()
{
	pInstance = new CollisionManager();
}

CollisionManager* CollisionManager::GetInstance()
{
	if (pInstance == nullptr) {
		CreateInstance();
	}

	return pInstance;
}

void CollisionManager::DestroyInstance()
{
	if (pInstance != nullptr) {
		delete pInstance;
		pInstance = nullptr;
	}
}

void CollisionManager::Render()
{
	for (auto pCol : pColliderArray) {
		if (pCol != nullptr) {
			pCol->Render();
		}
	}
}

/*
* @function	Update
* @brief	更新処理
*/
void CollisionManager::Update()
{
	// 一元管理排列内の全ての要素に総当たりで衝突検知を行う。
	for (int i = 0; i < currents.size(); i++) {
		for (int j = i + 1; j < currents[i].size(); j++) {
			if (pColliderArray[i] == nullptr || pColliderArray[j] == nullptr ||
				!pColliderArray[i]->GetGameObject()->IsVisible() || !pColliderArray[i]->IsEnable() ||
				!pColliderArray[j]->GetGameObject()->IsVisible() || !pColliderArray[j]->IsEnable()) {
				prevs[i][j] = false;
				currents[i][j] = false;
				continue;
			}
			currents[i][j] = CheckHit(pColliderArray[i], pColliderArray[j]);

			// 当たった瞬間
			if (!prevs[i][j] && currents[i][j])
			{
				// OnTrigger
				pColliderArray[i]->GetGameObject()->OnTriggerEnter(pColliderArray[j]);
				pColliderArray[j]->GetGameObject()->OnTriggerEnter(pColliderArray[i]);
			}
			else if (currents[i][j]) {
				//OnStay
				pColliderArray[i]->GetGameObject()->OnTriggerStay(pColliderArray[j]);
				pColliderArray[j]->GetGameObject()->OnTriggerStay(pColliderArray[i]);
			}
			if (prevs[i][j] && !currents[i][j]) {
				// OnExit
				pColliderArray[i]->GetGameObject()->OnTriggerExit(pColliderArray[j]);
				pColliderArray[j]->GetGameObject()->OnTriggerExit(pColliderArray[i]);

			}


			// 1フレーム前の衝突結果を更新
			prevs[i][j] = currents[i][j];
		}
	}
}

/*
* @function	Register
* @brief	一元管理に登録する
* @param[in]	Collider*	_pCol	登録する当たり判定
*/
void CollisionManager::Register(Collider* _pCol)
{
	// 管理配列に追加
	pColliderArray.push_back(_pCol);

	// 衝突結果判定にも追加
	prevs.push_back(std::vector<bool>());
	currents.push_back(std::vector<bool>());

	// 添え字のいんくりめんと
	index++;

	// 読み込んだ分だけ2次元配列を作る
	int i = 0;
	while (1) {
		// 生成する個数に達したらBreakする
		if (i == index) {
			break;
		}

		while (1) {
			if (currents[i].size() == index) {
				break;
			}

			prevs[i].push_back(false);
			currents[i].push_back(false);
		}
		i++;
	}
}

/*
* @function	UnRegister
* @brief	一元管理に登録する
* @param[in]	Collider*	_pCol	登録する当たり判定
*/
void CollisionManager::UnRegister(Collider* _pCol)
{
	// 2種類の考え方を記載

	// itratorの考え方
	auto itr = std::find(pColliderArray.begin(), pColliderArray.end(), _pCol);

	// itratorが末尾まで進んだ場合が、_pColが無かった時
	if (itr == pColliderArray.end()) {
		return;
	}

	// 配列の要素の考え方
	int index = -1;

	// 配列の中に検索する要素があるかどうか検索
	for (int i = 0; i < pColliderArray.size(); i++) {
		if (*itr == _pCol) {
			index = i;	// あったら要素番号を保存しておく。
			break;
		}
	}

	// 指定された要素を削除する
	pColliderArray.erase(itr);

	for (auto p : prevs) {
		p.erase(p.begin() + index);
	}
	prevs.erase(prevs.begin() + index);

	for (auto c : currents) {
		c.erase(c.begin() + index);
	}
	currents.erase(currents.begin() + index);

}


/*
* @function	CheckHit
* @brief	当たり判定の衝突検知
* @param[in]	Collider* _pCol1	当たり判定1
* @param[in]	Collider* _pCol2	当たり判定2
* @return		bool
*/
bool CollisionManager::CheckHit(Collider* _pCol1, Collider* _pCol2)
{
	// ダウンキャストを利用して当たり判定を振り分ける
	// 
	// アップキャスト：派生 is 基底の関係 == 犬は哺乳類だ -> 安全(100%正しい)
	// ダウンキャスト：基底 is 派生の関係 == 哺乳類は犬だ -> 危険(犬に対して操作した場合のみ正しい)
	//
	// ダウンキャストを行う場合は dynamic_cast<>() を利用する
	// dinamic_cast
	// →従来のC言語のキャストとほぼ一緒、どんな型でも書かれていたらやる、出来なかったらエラーが出る
	// →ポインタキャストの場合、エラーではなくnullptrを返す。
	// 対してstatic_castというものも存在する
	// →従来のC言語のキャストとほぼ一緒、どんな型でも書かれていたらやる、出来なかったらエラーが出る

	//Collider p();
	//char a = (char)p;
	//char b = static_cast<char>(p);
	//char c = dynamic_cast<char>(p);

	  // BOX-..
	{
		// 引数の_pCol1がBoxCollider*なのかを調べる
		auto tmp1 = dynamic_cast<BoxCollider*>(_pCol1);
		if (tmp1 != nullptr) {

			// BOX-BOX
			{
				auto tmp2 = dynamic_cast<BoxCollider*>(_pCol2);
				if (tmp2 != nullptr) {
					VECTOR minPoint1 = tmp1->GetMinPoint();
					VECTOR minPoint2 = tmp2->GetMinPoint();
					VECTOR maxPoint1 = tmp1->GetMaxPoint();
					VECTOR maxPoint2 = tmp2->GetMaxPoint();

					// 衝突の検知
					if ((minPoint1.x <= maxPoint2.x && minPoint2.x <= maxPoint1.x) &&
						(minPoint1.y <= maxPoint2.y && minPoint2.y <= maxPoint1.y) &&
						(minPoint1.z <= maxPoint2.z && minPoint2.z <= maxPoint1.z)) {
						return true;
					}

				}
			}
			// BOX-sphere
			{
				auto tmp2 = dynamic_cast<SphereCollider*>(_pCol2);
				// BOX-BOX
				if (tmp2 != nullptr)
				{

				}
			}
			// BOX-capsule
			{
				auto tmp2 = dynamic_cast<CapsuleCollider*>(_pCol2);
				// BOX-BOX
				if (tmp2 != nullptr)
				{

				}
			}
		}
	}

	// sphere-..
	{
		// 引数の_pCol1がsphereCollider*なのかを調べる
		auto tmp1 = dynamic_cast<SphereCollider*>(_pCol1);
		if (tmp1 != nullptr) {

			// sphere-BOX
			{
				auto tmp2 = dynamic_cast<BoxCollider*>(_pCol2);
				if (tmp2 != nullptr) {
					VECTOR center1 = tmp1->GetWorldCenter();
					float radius = tmp1->GetRadius();

					// 衝突の検知
					//if ((minPoint1.x <= maxPoint2.x && minPoint2.x <= maxPoint1.x) &&
					//	(minPoint1.y <= maxPoint2.y && minPoint2.y <= maxPoint1.y) &&
					//	(minPoint1.z <= maxPoint2.z && minPoint2.z <= maxPoint1.z)) {
					//	return true;
					//}

				}
			}
			// sphere-sphere
			{
				auto tmp2 = dynamic_cast<SphereCollider*>(_pCol2);
				if (tmp2 != nullptr)
				{
					VECTOR center1 = tmp1->GetWorldCenter();
					VECTOR center2 = tmp2->GetWorldCenter();

					VECTOR delta = VSub(center1, center2);

					if (VSize(delta) < tmp1->GetRadius() + tmp2->GetRadius()) {
						return true;
					}

				}
			}
			// sphere-capsule
			{
				auto tmp2 = dynamic_cast<CapsuleCollider*>(_pCol2);
				// BOX-BOX
				if (tmp2 != nullptr)
				{

				}
			}
		}
	}

	// capsule-..
	{
		// 引数の_pCol1がCapsuleCollider*なのかを調べる
		auto tmp1 = dynamic_cast<CapsuleCollider*>(_pCol1);
		if (tmp1 != nullptr) {

			// capsule-BOX
			{
				auto tmp2 = dynamic_cast<BoxCollider*>(_pCol2);
				if (tmp2 != nullptr) {

				}
			}
			// capsule-sphere
			{
				auto tmp2 = dynamic_cast<SphereCollider*>(_pCol2);
				// BOX-BOX
				if (tmp2 != nullptr)
				{

				}
			}
			// capsule-capsule
			auto tmp2 = dynamic_cast<CapsuleCollider*>(_pCol2);
			// BOX-BOX
			{
				if (tmp2 != nullptr)
				{
					// 計算
					float distance = Segment_Segment_MinLength(
						tmp1->GetWorldPoint1(), tmp1->GetWorldPoint2(),
						tmp2->GetWorldPoint1(), tmp2->GetWorldPoint2()
					);

					// 当たりの検知：線分と線分の最短距離が半径の和より小さい
					if (distance <= tmp1->GetRadius() + tmp2->GetRadius()) {
						return true;
					}
				}
			}
		}
	}


	return false;
}
