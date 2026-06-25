#pragma once
#include <DxLib.h>

/// @brief DxLibの衝突判定関数をラップした名前空間
namespace DxLibCollisionMath
{
	/// @brief 球のデータ構造体
	struct Sphere
	{
		VECTOR center;	/// 球の中心座標
		float radius;	/// 球の半径

		Sphere()
		{
			center = VGet(0.0f, 0.0f, 0.0f);
			radius = 1.0f;
		}
	};

	/// @brief カプセルのデータ構造体
	struct Capsule
	{
		VECTOR top;
		VECTOR bottom;
		float radius;

		Capsule()
		{
			top = VGet(0.0f, 1.0f, 0.0f);
			bottom = VGet(0.0f, -1.0f, 0.0f);
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
		return HitCheck_Sphere_Sphere(a.center, a.radius, b.center, b.radius);
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
		return HitCheck_Capsule_Capsule(a.top, a.bottom, a.radius, b.top, b.bottom, b.radius);
	}
}

