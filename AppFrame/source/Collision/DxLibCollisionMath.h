#pragma once
#include <DxLib.h>
#include "VectorConverter/VectorConverter.h"
#include "Shape/Capsule.h"
#include "Shape/Sphere.h"

/// @brief DxLibの衝突判定関数をラップした名前空間
namespace DxLibCollisionMath
{
	/// @brief 球と球の衝突判定関数
	///
	/// @param a 球Aのデータ
	/// @param b 球Bのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	inline bool CheckSphereToSphere(
		const Collision::Shape::Sphere& a,
		const Collision::Shape::Sphere& b)
	{
		// 球と球の衝突判定
		return HitCheck_Sphere_Sphere
		(
			Vec::ToDxVec(a.center), 
			a.radius, 

			Vec::ToDxVec(b.center), 
			b.radius
		);
	}

	/// @brief カプセルとカプセルの衝突判定関数
	///
	/// @param a カプセルAのデータ
	/// @param b カプセルBのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	inline bool CheckCapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b)
	{
		// カプセル同士の衝突判定
		return HitCheck_Capsule_Capsule
		(
			Vec::ToDxVec(a.start), 
			Vec::ToDxVec(a.end), 
			a.radius, 

			Vec::ToDxVec(b.start), 
			Vec::ToDxVec(b.end),
			b.radius
		);
	}
}

