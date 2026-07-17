#pragma once
#include "DamageInfo.h"
#include "AttackData.h"
#include "Vector/Vector3.h"

namespace DamageConverter
{
	inline DamageInfo ConvertAttackDataToDamageInfo(const AttackData& attackData, const Vec3::Vector3& hitDirection)
	{
		DamageInfo damageInfo;
		damageInfo.damage		= attackData.damageData.damage;
		damageInfo.hitDirection = hitDirection;
		damageInfo.damageData	= attackData.knockbackData;
		return damageInfo;
	}
}