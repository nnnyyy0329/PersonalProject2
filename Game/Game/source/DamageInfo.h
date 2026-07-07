#pragma once
#include "DamageData.h"
#include "Vector/Vector3.h"

/// @brief 被弾情報構造体
struct DamageInfo
{
	DamageData damageData;		// 被弾性能
	Vec3::Vector3 hitDirection;	// ヒット方向

	DamageInfo()
	{
		damageData = DamageData();
		hitDirection = Vec3::Vector3(0.0f, 0.0f, 0.0f);
	}
};