#pragma once
#include "../Collision/Shape/Capsule.h"
#include "../Collision/Shape/Sphere.h"

namespace HitCheck
{
	/// @brief 球と球の衝突判定関数
	///
	/// @param a 球Aのデータ
	/// @param b 球Bのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	bool SphereToSphere(
		const Collision::Shape::Sphere& a,
		const Collision::Shape::Sphere& b);

	/// @brief カプセルとカプセルの衝突判定関数
	///
	/// @param a カプセルAのデータ
	/// @param b カプセルBのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	bool CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b);
}
