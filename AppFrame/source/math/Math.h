#pragma once
#include "../Vector/Vector3.h"
//#include "../Collision/Shape/Capsule.h"
//#include "../Collision/Shape/Sphere.h"

namespace Math
{
	/// @brief クランプ関数
	///
	/// @param value 値
	/// @param min 最小値
	/// @param max 最大値
	/// 
	/// @return min <= value <= max の範囲に収めた値
	float Clamp(float value, float min, float max);

	/// @brief 2つの線分間の最短距離の二乗を計算する関数
	///
	/// @param startA 線分Aの開始点
	/// @param endA 線分Aの終了点
	/// @param startB 線分Bの開始点
	/// @param endB 線分Bの終了点
	/// 
	/// @return 2つの線分間の最短距離の二乗
	float CalcSegmentToSegmentDistanceSq(
		const Vec3::Vector3& startA,
		const Vec3::Vector3& endA,
		const Vec3::Vector3& startB,
		const Vec3::Vector3& endB);

	/// @brief 点と線分の最短距離を計算する関数
	///
	/// @param point 点の座標
	/// @param segmentStart 線分の開始点
	/// @param segmentEnd 線分の終了点
	/// 
	/// @return 点と線分の最短距離
	Vec3::Vector3 ClosestPointOnSegment(
		const Vec3::Vector3& point,
		const Vec3::Vector3& segmentStart,
		const Vec3::Vector3& segmentEnd);

	
}