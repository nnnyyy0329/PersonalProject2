#pragma once
#include "Character.h"
#include "math/Math.h"
#include "Collision/HitCollision.h"
#include <limits>

namespace JudgementMath
{
	/// @brief 2人のキャラクター間の距離を計算する関数
	///
	/// @param character1 キャラクター1
	/// @param character2 キャラクター2
	/// 
	/// @return キャラクター間の距離
	inline float DistanceToCharacters(const Character& character1, const Character& character2)
	{
		Vec3::Vector3 pos1 = character1.GetObjectData().pos;
		Vec3::Vector3 pos2 = character2.GetObjectData().pos;
		return (pos1 - pos2).Length();
	}

	/// @brief キャラクターが指定の範囲内にいるかどうかを判定する関数
	/// 
	/// @param character1 キャラクター1
	/// @param character2 キャラクター2
	/// @param range 範囲
	/// 
	/// @return 範囲内にいるかどうか
	inline bool IsCharacterInRange(const Character& character1, const Character& character2, float range)
	{
		return DistanceToCharacters(character1, character2) <= range;
	}

}