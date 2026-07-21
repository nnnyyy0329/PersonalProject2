#pragma once

// @brief 攻撃データ構造体
struct AttackTiming
{
	float startTime;		/// 攻撃開始時間
	float activeDuration;	/// 攻撃が有効な時間
	float recoveryDuration;	/// 攻撃後の硬直時間
	float comboReceiveTime;	/// コンボ受付時間（ recoveryDuration のフレーム数よりも少ない値にしなければならない）
	bool isAutoNextAttack;	/// 次の攻撃を自動で発動するかどうか

	AttackTiming()
	{
		startTime			= 0.0f;
		activeDuration		= 0.0f;
		recoveryDuration	= 0.0f;
		comboReceiveTime	= 0.0f;
		isAutoNextAttack	= false;
	}
};