#pragma once

// @brief エフェクトデータクラス
struct EffectData
{
	int handle;		/// エフェクトハンドル
	float scale;	/// エフェクトのスケール
	float lifeTime;	/// エフェクトの寿命

	EffectData()
	{
		handle		= -1;
		scale		= 1.0f;
		lifeTime	= 0.0f;
	}
};