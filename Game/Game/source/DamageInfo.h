#pragma once
#include "KnockbackData.h"
#include "Vector/Vector3.h"

/// @brief 被弾情報構造体
struct DamageInfo
{
	float damage;				/// ダメージ量
	Vec3::Vector3 hitDirection;	/// ヒット方向
	KnockbackData damageData;	/// ノックバックデータ

	DamageInfo()
	{
		damage = 0.0f;
		hitDirection = Vec3::Vector3(0.0f, 0.0f, 0.0f);
		damageData = KnockbackData();
	}
};