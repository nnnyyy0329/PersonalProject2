#pragma once
#include "DamageInfo.h"
#include "AttackData.h"
#include "Vector/Vector3.h"

namespace DamageConverter
{
	/// @brief 攻撃データをダメージ情報に変換する関数
	///
	/// @param attackData 攻撃データ
	/// @param hitDirection ヒット方向
	/// 
	/// @return ダメージ情報
	inline DamageInfo ConvertAttackDataToDamageInfo(const AttackData& attackData, const Vec3::Vector3& hitDirection)
	{
		DamageInfo damageInfo;

		damageInfo.damage		= attackData.damageData.damage;
		damageInfo.hitDirection = hitDirection;
		damageInfo.damageData	= attackData.knockbackData;

		return damageInfo;
	}
}