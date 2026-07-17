#pragma once
#include "Vector/Vector3.h"

/// @brief ノックバックデータ構造体
struct KnockbackData
{
	Vec3::Vector3 moveDirection;	/// 移動方向
	float knockbackSpeed;			/// ノックバック速度
	float knockbackTime;			/// ノックバック時間

	KnockbackData()
	{
		moveDirection = Vec3::Vector3(0.0f, 0.0f, 0.0f);
		knockbackSpeed = 0.0f;
		knockbackTime = 0.0f;
	}
};