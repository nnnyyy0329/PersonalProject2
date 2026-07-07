#pragma once
#include "Vector/Vector3.h"

/// @brief キャラクターの当たり判定データ構造体
struct CharColData
{
	Vec3::Vector3 top;		/// キャラクターのカプセル形状の上端の位置
	Vec3::Vector3 bottom;	/// キャラクターのカプセル形状の下端の位置
	float radius;			/// キャラクターのカプセル形状の半径

	CharColData()
	{
		top = { 0.0f, 0.0f, 0.0f };
		bottom = { 0.0f, 0.0f, 0.0f };
		radius = 0.0f;
	}
};