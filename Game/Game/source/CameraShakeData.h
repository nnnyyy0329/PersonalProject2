#pragma once

/// @brief カメラ揺れデータ構造体
struct CameraShakeData
{
	float duration;		/// 揺れの持続時間
	float magnitude;	/// 揺れの大きさ[
	float decay;		/// 揺れの減衰率

	CameraShakeData()
	{
		duration	= 0.0f;
		magnitude	= 0.0f;
		decay	= 0.0f;
	}
};