#pragma once
#include <string>

// @brief サウンドデータ構造体
struct SoundData
{
	std::string name1;	/// サウンド1の名前
	std::string name2;	/// サウンド2の名前
	float volume;		/// 音量

	SoundData()
	{
		name1 = "";
		name2 = "";
		volume = 1.0f;
	}
};