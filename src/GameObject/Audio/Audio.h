#pragma once
#include "../GameObject.h"
/*
* @brief 音源オブジェクト
*/
class Audio : public GameObject
{
private:	// メンバ変数
	bool is3DSound;				//3Dサウンド化どうか
	bool isLoop;				// ループの有無
	int soundHandle;			// 音声ファイルのハンドル
	float volume;				// 音量
	float distance;				// 聞こえる範囲

public:		// コンストラクタデストラクタ
	// コンストラクタ
	/*
	* @brief	コンストラクタ
	* @param[in]	int	_soundHandle	音声ハンドル
	* @param[in]	bool	_is3D		3D音源かのフラグ
	*/
	Audio(int _soundHandle, bool _is3D = false);

	~Audio();

public:		// オーバーライドするメンバ関数
	void Start() override;
	void Update() override;
	void Render() override;

public:		// メンバ関数
public:		// アクセサ

	/// <summary>
	///  音ハンドルの取得
	/// </summary>
	/// <returns></returns>
	inline int GetSoundHandle() { return soundHandle; }

	/// <summary>
	/// ループ再生の変更
	/// </summary>
	/// <param name="_b"></param>
	inline void setIsLoop(bool _b) { isLoop = _b; }

	/// <summary>
	/// 音量の変更
	/// </summary>
	/// <param name="_v"></param>
	inline void setVolume(float _v) {
		volume = _v * 255;
		if (volume < 0) {
			volume = 0;
		}
		if (volume > 255) {
			volume = 255;
		}
	}



};

