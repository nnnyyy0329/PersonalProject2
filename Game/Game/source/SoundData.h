#pragma once

// @brief サウンドデータ構造体
struct SoundData
{
	int handle;		/// サウンドハンドル
	float volume;	/// 音量

	SoundData()
	{
		handle = -1;
		volume = 1.0f;
	}
};