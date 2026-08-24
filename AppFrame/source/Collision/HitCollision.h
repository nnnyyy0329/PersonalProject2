#pragma once
#include "../Collision/Shape/Capsule.h"
#include "../Collision/Shape/Sphere.h"

namespace HitCheck
{
	/// @brief カプセル同士の衝突判定結果を表す構造体
	struct CapsuleCollisionResult
	{
		Vec3::Vector3 normal;	// 衝突面の法線ベクトル
		float penetration;		// 衝突の貫通深さ
		bool isHit;				// 衝突しているかどうか

		CapsuleCollisionResult()
		{
			normal		= Vec3::Vector3(0.0f, 0.0f, 0.0f);
			penetration = 0.0f;
			isHit		= false;
		}
	};

	/// @brief 球と球の衝突判定関数
	///
	/// @param a 球Aのデータ
	/// @param b 球Bのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	bool SphereToSphere(
		const Collision::Shape::Sphere& a,
		const Collision::Shape::Sphere& b);

	/*/// @brief カプセルとカプセルの衝突判定関数
	///
	/// @param a カプセルAのデータ
	/// @param b カプセルBのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	bool CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b);*/

	/// @brief カプセル同士の衝突判定の計算関数
	///
	/// @param a カプセルAのデータ
	/// @param b カプセルBのデータ
	/// 
	/// @return ヒット結果を含む構造体
	CapsuleCollisionResult CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b);
}
