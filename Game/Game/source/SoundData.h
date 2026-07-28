#pragma once
#include <string>

// @brief サウンドデータ構造体
struct SoundData
{
	std::string name;	/// サウンドの名前
	float volume;		/// 音量

	SoundData()
	{
		name = "";
		volume = 1.0f;
	}
};