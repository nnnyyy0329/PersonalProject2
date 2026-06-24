#pragma once
#include <string>
#include "CollisionData.h"

/// @brief 攻撃のフェーズを表す列挙型
enum class AttackPhase
{
	NONE,
	STARTUP,	///< 攻撃開始
	ACTIVE,		///< 攻撃が有効
	RECOVERY	///< 攻撃後の硬直
};

/// @brief 攻撃データ構造体
struct AttackData
{
	float startTime;		/// 攻撃開始時間
	float activeDuration;	/// 攻撃が有効な時間
	float recoveryDuration;	/// 攻撃後の硬直時間
	float comboReceiveTime;	/// コンボ受付時間（ recoveryDuration のフレーム数よりも少ない値にしなければならない）
	CollisionData colData;	/// 当たり判定のデータ

	AttackData()
	{
		startTime			= 0.0f;
		activeDuration		= 0.0f;
		recoveryDuration	= 0.0f;
		comboReceiveTime	= 0.0f;
		colData				= CollisionData();
	}
};