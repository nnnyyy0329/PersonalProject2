#pragma once
#include "../Vector/Vector3.h"

namespace Math
{
	// 円周率
	constexpr float PI = 3.14159265358979323846f;

	// 0に近い値を比較するための定数
	constexpr float EPSILON = 0.00001f;

	/// @brief 線分間の最近接点を表す構造体
	struct SegmentClosestPoints
	{
		Vec3::Vector3 pointA;		// 線分A上の最近接点
		Vec3::Vector3 pointB;		// 線分B上の最近接点
		float distanceSq = 0.0f;	// 線分間の最短距離の二乗

		SegmentClosestPoints()
		{
			pointA		= Vec3::Vector3(0.0f, 0.0f, 0.0f);
			pointB		= Vec3::Vector3(0.0f, 0.0f, 0.0f);
			distanceSq	= 0.0f;
		}
	};

	/// @brief クランプ関数
	///
	/// @tparam T 型
	/// 
	/// @param value 値
	/// @param min 最小値
	/// @param max 最大値
	/// 
	/// @return valueをminとmaxの範囲にクランプした値
	template  <typename T>
	constexpr T Clamp(T value, T min, T max)
	{
		if(value < min) { return min; }
		if(value > max) { return max; }
		return value;
	}

	/// @brief abs関数
	///
	/// @tparam T 型
	/// 
	/// @param value 値
	/// 
	/// @return valueの絶対値
	template <typename T>
	constexpr T Abs(T value)
	{
		return (value < 0) ? -value : value;
	}

	/// @brief Sqr関数
	///
	/// @tparam T 型
	/// 
	/// @param value 値
	/// 
	/// @return valueの二乗
	template <typename T>
	constexpr T Sqr(T value)
	{
		return value * value;
	}

	/// @brief 最小値を返す関数
	///
	/// @tparam T 型
	/// 
	/// @param value1 値1
	/// @param value2 値2
	/// 
	/// @return value1とvalue2のうち小さい方の値
	template <typename T>
	constexpr T Min(T value1, T value2)
	{
		return (value1 < value2) ? value1 : value2;
	}

	/// @brief 最大値を返す関数
	///
	/// @tparam T 型
	/// 
	/// @param value1 値1
	/// @param value2 値2
	/// 
	/// @return value1とvalue2のうち大きい方の値
	template <typename T>
	constexpr T Max(T value1, T value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	/// @brief 2つの線分間の最近接点を計算する関数
	///
	/// @param startA 線分Aの開始点
	/// @param endA 線分Aの終了点
	/// @param startB 線分Bの開始点
	/// @param endB 線分Bの終了点
	/// 
	/// @return 線分Aと線分Bの最近接点と距離の二乗
	SegmentClosestPoints CalcSegmentClosestPoints(
		const Vec3::Vector3& startA,
		const Vec3::Vector3& endA,
		const Vec3::Vector3& startB,
		const Vec3::Vector3& endB);

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

	/// @brief 点から線分上の最近接点を計算する関数
	///
	/// @param point 点の座標
	/// @param segmentStart 線分の開始点
	/// @param segmentEnd 線分の終了点
	///
	/// @return 線分上にあるpointからの最近接点
	Vec3::Vector3 ClosestPointOnSegment(
		const Vec3::Vector3& point,
		const Vec3::Vector3& segmentStart,
		const Vec3::Vector3& segmentEnd);

	
}