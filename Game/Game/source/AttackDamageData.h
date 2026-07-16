#pragma once

/// @brief 攻撃ダメージデータ構造体
struct AttackDamageData
{
	float damage;				/// ダメージ量
	float hitStunTime;			/// ヒットスタン時間
	float damageInvincibeTime;	/// ダメージ無敵時間
	bool isLaunch;				/// 打ち上げフラグ

	AttackDamageData()
	{
		damage = 0.0f;
		hitStunTime = 0.0f;
		damageInvincibeTime = 0.0f;
		isLaunch = false;
	}
};