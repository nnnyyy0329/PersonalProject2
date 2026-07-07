#pragma once
#include <DxLib.h>
#include "Vector/Vector3.h"
#include "VectorConverter/VectorConverter.h"

/// @brief DxLibの衝突判定関数をラップした名前空間
namespace DxLibCollisionMath
{
	/// @brief 球のデータ構造体
	struct Sphere
	{
		Vec3::Vector3 center;	/// 球の中心座標
		float radius;			/// 球の半径

		Sphere()
		{
			center = Vec3::Vector3(0.0f, 0.0f, 0.0f);
			radius = 1.0f;
		}
	};

	/// @brief カプセルのデータ構造体
	struct Capsule
	{
		Vec3::Vector3 top;		/// カプセルの上端の座標
		Vec3::Vector3 bottom;	/// カプセルの下端の座標
		float radius;			/// カプセルの半径

		Capsule()
		{
			top = Vec3::Vector3(0.0f, 1.0f, 0.0f);
			bottom = Vec3::Vector3(0.0f, -1.0f, 0.0f);
			radius = 1.0f;
		}
	};

	/// @brief 球と球の衝突判定関数
	///
	/// @param a 球Aのデータ
	/// @param b 球Bのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	inline bool CheckSphereToSphere(const Sphere& a, const Sphere& b)
	{
		//// 球の中心間の距離を計算
		//VECTOR diff = VSub(a.center, b.center);

		//// 球の中心間の距離を計算
		//float distance = VSize(diff);

		//// 球の半径の合計を計算
		//float radiusSum = a.radius + b.radius;

		//// 距離が半径の合計より小さい場合、衝突していると判断
		//return distance < radiusSum;

		// 球と球の衝突判定
		return HitCheck_Sphere_Sphere
		(
			Vec::ToDxVec(a.center), a.radius, 
			Vec::ToDxVec(b.center), b.radius
		);
	}

	/// @brief カプセルとカプセルの衝突判定関数
	///
	/// @param a カプセルAのデータ
	/// @param b カプセルBのデータ
	/// 
	/// @return 衝突している場合はtrue、そうでない場合はfalse
	inline bool CheckCapsuleToCapsule(const Capsule& a, const Capsule& b)
	{
		// カプセル同士の衝突判定
		return HitCheck_Capsule_Capsule
		(
			Vec::ToDxVec(a.top), Vec::ToDxVec(a.bottom), a.radius, 
			Vec::ToDxVec(b.top), Vec::ToDxVec(b.bottom), b.radius
		);
	}
}

