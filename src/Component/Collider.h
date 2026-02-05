#pragma once
#include "../GameObject/GameObject.h";
#include <DxLib.h>

/*
* @brief	当たり判定の基底class
* @tips		UnityのisTriggerの状態のようなもの
*/
class Collider
{
protected:
	bool isEnable;				// 当たり判定の有効・無効
	GameObject* pGameObject;	// 当たり判定をつけるオブジェクト
	MATRIX mat;				// 当たり判定をつける

public:	//コンストラクタ・デストラクタ
	Collider(GameObject* _pObj);

	virtual ~Collider();


public:	// メンバ関数
	virtual void Update() = 0;

	virtual void Render() = 0;

public:		// アクセッサ

	bool IsEnable() const { return  isEnable; }

	void SetEnable(bool _v) {
		isEnable = _v;
	}
	// 当たり判定を付けるオブジェクトの取得
	inline GameObject* GetGameObject() const { return pGameObject; }

	inline void SetGameObject(GameObject* _pobj) { pGameObject = _pobj; }


	inline void SetMatrix(MATRIX _mat) { mat = _mat; }
};

/*
* @brief	当たり判定 box
* @tips		サンプルには使用しないが、基本なのでしっかり覚える
*			boxcolliderには軸中心のものとそうでないものがある
*			軸中心のものをAxis Aligned Bounding Box(AABB)
*			そうでないものをOrientedBounding xox(OBB)
*
*			今回はAABBの実装・当たり判定は回転しないものとする
*			計算方法は２次元と同じ。軸が一つ増える。
*
*/
class BoxCollider :public Collider {
private:
	VECTOR originMinPoint;
	VECTOR originMaxPoint;

	VECTOR originVertex[8];		//頂点データ
	VECTOR localVertex[8];		//頂点データ
	VECTOR worldVertex[8];		//頂点データ

public:		// コンストラクタとデストラクタ

	/*
	* @brief コンストラクタ
	*/
	BoxCollider(GameObject* _pObj, VECTOR _min, VECTOR _max);

	/*
	* @brief デストラクタ
	*/
	~BoxCollider() = default;

public:		// オーバーライドしたメンバ関数

	/*
	* @brief	更新処理
	*/
	void Update() override;

	/*
	* @brief	描画処理
	*/
	void Render() override;
public:
	inline VECTOR GetMinPoint() const { return worldVertex[0]; }
	inline VECTOR GetMaxPoint() const { return worldVertex[7]; }
};

/*
* @brief 当たり判定球体
*/
class SphereCollider : public Collider {
private:
	VECTOR localCenter;
	VECTOR worldCenter;
	float radius;

public:		// こんすとらくた・デストラクタ
	/*
	* @brief コンストラクタ
	*/
	SphereCollider(GameObject* _pObj, VECTOR _offset, float _radius);

	/*
	* @brief デストラクタ
	*/
	~SphereCollider() = default;

public:
	void Update() override;

	void Render() override;

public:		// げったせった
	inline VECTOR GetWorldCenter() const { return worldCenter; }
	inline float GetRadius() const { return radius; }

};


/*
* @brief 当たり判定カプセル
* @tips カプセルを構成するには1つの線分と半径が必要
*		線分->2点間の直線
*/
class CapsuleCollider : public Collider {
private:
	VECTOR	originPoint1, originPoint2;		// 線分を構成する2点
	float radius;							// 半径
	VECTOR offset;
	VECTOR localPoint1, localPoint2;
	VECTOR worldPoint1, worldPoint2;

public:		// こんすとらくた・デストラクタ
	/*
	* @brief コンストラクタ
	* @param[in]	GameObject* _pObj	判定をセットするオブジェクト
	* @param[in]	VECTOR		p1		線分の点1
	* @param[in]	VECTOR		p2		線分の点2
	* @param[in]	float		_radius	半円の半径
	*
	*/
	CapsuleCollider(GameObject* _pObj, VECTOR _p1, VECTOR _p2, float _radius);

	/*
	* @brief デストラクタ
	*/
	~CapsuleCollider() = default;

public:
	void Update() override;

	void Render() override;

public:		// げったせった
	/*
	* @function		GFetWorldPoint1
	* @brief		線分の始点を取得
	* @return		VECTOR
	*/
	inline VECTOR GetWorldPoint1() const { return worldPoint1; }
	/*
	* @function		GFetWorldPoint2
	* @brief		線分の始点を取得
	* @return		VECTOR
	*/
	inline VECTOR GetWorldPoint2() const { return worldPoint2; }

	inline float GetRadius() const { return radius; }
};





