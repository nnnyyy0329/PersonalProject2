#pragma once
#include "Character.h"
#include "Collision/DxLibCollisionMath.h"
#include "CollisionComponent.h"
#include "GeometryUtility/DxLibGeometryUtility.h"
#include <optional>
#include "Vector/Vector3.h"
#include "VectorConverter/VectorConverter.h"

/// @brief キャラクターの当たり判定形状を作成する関数群
namespace CollisionShapeBuilder
{
	/// @brief キャラクターのカプセル形状を作成する関数
	///
	/// @param character カプセル形状を作成するキャラクター
	/// 
	/// @return キャラクターのカプセル形状
	inline std::optional<Collision::Shape::Capsule> CreateCharacterCapsule(const Character& character)
	{
		Collision::Shape::Capsule capsule;

		// キャラクターの当たり判定データを取得してカプセル形状に設定する
		capsule.start	= character.GetCharColData().top;
		capsule.end		= character.GetCharColData().bottom;
		capsule.radius	= character.GetCharColData().radius;

		return capsule;
	}

	/// @brief キャラクターの攻撃判定カプセル形状を作成する関数
	///
	/// @param character 攻撃判定カプセル形状を作成するキャラクター
	/// 
	/// @return キャラクターの攻撃判定カプセル形状
	inline std::optional<Collision::Shape::Capsule> CreateAttackCapsule(Character& character)
	{
		Collision::Shape::Capsule capsule;

		// キャラクターの攻撃判定データを取得してカプセル形状に設定する
		auto attackCol = character.GetComponent<CollisionComponent<Character>>();
		if(attackCol && attackCol->IsActive())
		{
			// 攻撃判定のデータを取得
			auto& attackData = attackCol->GetCollisionData();

			// キャラクターの回転角度から前方向ベクトルを取得
			Vec3::Vector3 forward = 
				Vec::ToVec3(DxLibGeometryUtility::GetForwardVector(character.GetObjectData().rot.GetY()));

			// キャラクターの回転角度から右方向ベクトルを取得
			Vec3::Vector3 right = 
				Vec::ToVec3(DxLibGeometryUtility::GetRightVector(character.GetObjectData().rot.GetY()));

			// 攻撃判定の上端のオフセットを計算
			Vec3::Vector3 topOffset = 
				(
					right * attackData.topOffset.GetX() + Vec3::Vector3(0.0f, attackData.topOffset.GetY(), 0.0f) + (forward * attackData.topOffset.GetZ())
				);

			// 攻撃判定の下端のオフセットを計算
			Vec3::Vector3 bottomOffset = 
				(
					right * attackData.bottomOffset.GetX() + Vec3::Vector3(0.0f, attackData.bottomOffset.GetY(), 0.0f) + (forward * attackData.bottomOffset.GetZ())
				);

			// キャラクターの位置と攻撃判定データを使用してカプセル形状を設定する
			capsule.start	= character.GetObjectData().pos + topOffset;
			capsule.end		= character.GetObjectData().pos + bottomOffset;
			capsule.radius	= attackData.radius;
		}

		return capsule;
	}
}