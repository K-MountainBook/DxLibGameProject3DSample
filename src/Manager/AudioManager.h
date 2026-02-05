#pragma once
#include <map>
#include <string>
#include <list>
#include <DxLib.h>

class AudioManager
{
#pragma region シングルトンのデータ構造

private:
	static AudioManager* pInstance;
private:	// コンストラクタとデストラクタ
	/*
	* @brief コンストラクタ
	* @tips  外部で生成されないようにアクセス修飾子をprivateにする。
	*/
	AudioManager();

	/*
	* @brief デストラクタ
	*/
	~AudioManager();

public:		// コピーと譲渡の禁止
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;

	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;


private:	// 静的メンバ関数
	/*
	* @function	CreateInstance
	* @brief	自身のインスタンスを生成する。
	*/
	static void CreateInstance();


public:		// 静的メンバ関数
	/*
	* @function GetInstance
	* @brief	自身のインスタンスを取得する唯一の手段
	* @return	InputManager*	自身のインスタンスのアドレス
	*/
	static AudioManager* GetInstance();

	/*
	* @function	DestroyInstance
	* @brief	自身のインスタンスを破棄する
	*/
	static void DestroyInstance();

#pragma endregion

private:	// 静的メンバ

	std::map<std::string, int> audioResourceMap;
	std::list<class Audio*> pAudioList;

	

public:
	/// <summary>
	/// エフェクトの読み込み
	/// </summary>
	/// <param name="_filePath">ファイルパス</param>
	/// <param name="_name">音につける名前</param>
	/// <param name="_magnification">3Dかどうか？</param>
	void Load(std::string _filePath, std::string _name, bool _is3D = false);


	/// <summary>
	/// 音量の変更
	/// </summary>
	/// <param name="_name">変更する音の名前</param>
	/// <param name="_volume">変更値0～1</param>
	void ChangeVolume(std::string _name, float _volume);

	/// <summary>
	/// 音の再生
	/// </summary>
	/// <param name="_name">再生する音の名前</param>
	/// <param name="_volume">音量(0.0f～1.0f)</param>
	void PlayOneShot(std::string _name, float _volume = 1.0f);

	/// <summary>
	/// 音源の設置
	/// </summary>
	/// <param name="_name">再生する音の名前</param>
	/// <param name="_pos">接地する場所</param>
	/// <param name="_volume">音量</param>
	/// <param name="isLoop">ループの有無</param>
	void PlayClipAtPoint(std::string _name, VECTOR _pos, float _volume = 1.0f, bool isLoop = false);

	/// <summary>
	/// 音の停止
	/// </summary>
	/// <param name="_name">停止する音の名前</param>
	void Stop(std::string _name);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

};

