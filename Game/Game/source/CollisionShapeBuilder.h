#pragma once
#include "Character.h"
#include "Collision/DxLibCollisionMath.h"
#include "CollisionComponent.h"
#include <optional>

/// @brief キャラクターの当たり判定形状を作成する関数群
namespace CollisionShapeBuilder
{
	/// @brief キャラクターのカプセル形状を作成する関数
	///
	/// @param character カプセル形状を作成するキャラクター
	/// 
	/// @return キャラクターのカプセル形状
	inline std::optional<DxLibCollisionMath::Capsule> CreateCharacterCapsule(const Character& character)
	{
		DxLibCollisionMath::Capsule capsule;

		// キャラクターの当たり判定データを取得してカプセル形状に設定する
		capsule.top		= character.GetCharColData().top;
		capsule.bottom	= character.GetCharColData().bottom;
		capsule.radius	= character.GetCharColData().radius;

		return capsule;
	}

	/// @brief キャラクターの攻撃判定カプセル形状を作成する関数
	///
	/// @param character 攻撃判定カプセル形状を作成するキャラクター
	/// 
	/// @return キャラクターの攻撃判定カプセル形状
	inline std::optional<DxLibCollisionMath::Capsule> CreateAttackCapsule(Character& character)
	{
		DxLibCollisionMath::Capsule capsule;

		// キャラクターの攻撃判定データを取得してカプセル形状に設定する
		auto attackCol = character.GetComponent<CollisionComponent<Character>>();

		if(attackCol && attackCol->IsActive())
		{
			// 攻撃判定のデータを取得
			auto& attackData = attackCol->GetCollisionData();

			// キャラクターの位置と攻撃判定データを使用してカプセル形状を設定する
			capsule.top		= VAdd(character.GetObjectData().pos, attackData.offset);
			capsule.bottom	= VAdd(character.GetObjectData().pos, attackData.offset);
			capsule.radius	= attackData.radius;
		}

		return capsule;
	}
}