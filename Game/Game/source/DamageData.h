#pragma once

/// @brief 被弾性能構造体
struct DamageData
{
	float damage;				// ダメージ量
	float knockback;			// ノックバック量
	float hitStunTime;			// ヒットスタン時間
	float damageInvincibeTime;	// ダメージ無敵時間
	bool isLaunch;				// 打ち上げフラグ

	DamageData()
	{
		damage				= 0.0f;
		knockback			= 0.0f;
		hitStunTime			= 0.0f;
		damageInvincibeTime = 0.0f;
		isLaunch			= false;
	}
};