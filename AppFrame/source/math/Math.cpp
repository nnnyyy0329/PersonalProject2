#include "Math.h"

namespace Math
{
	float Clamp(float value, float min, float max)
	{
		if(value < min) { return min; }
		if(value > max) { return max; }
		return value;
	}

	float CalcSegmentToSegmentDistanceSq(
		const Vec3::Vector3& startA,
		const Vec3::Vector3& endA,
		const Vec3::Vector3& startB,
		const Vec3::Vector3& endB)
	{
		Vec3::Vector3 segmentA	= endA - startA;	// 線分Aのベクトル
		Vec3::Vector3 segmentB	= endB - startB;	// 線分Bのベクトル
		Vec3::Vector3 r			= startA - startB;	// 線分Aの開始点から線分Bの開始点までのベクトル

		float segmentALengthSq		= segmentA.Dot(segmentA);	// 線分Aの長さの二乗
		float segmentBLengthSq		= segmentB.Dot(segmentB);	// 線分Bの長さの二乗

		// 線分Aの長さが0に近い場合、線分Aは点として扱う
		if(Math::Abs(segmentALengthSq) < Math::EPSILON)
		{
			// 線分Aが点の場合、線分B上の最近接点を求める
			Vec3::Vector3 closestB = ClosestPointOnSegment(startA, startB, endB);
			Vec3::Vector3 diff = startA - closestB;
			return diff.Dot(diff);
		}

		// 線分Bの長さが0に近い場合、線分Bは点として扱う
		if(Math::Abs(segmentBLengthSq) < Math::EPSILON)
		{
			// 線分Bが点の場合、線分A上の最近接点を求める
			Vec3::Vector3 closestA = ClosestPointOnSegment(startB, startA, endA);
			Vec3::Vector3 diff = startB - closestA;
			return diff.Dot(diff);
		}

		float segmentDirectionDot	= segmentA.Dot(segmentB);	// 線分Aと線分Bの方向ベクトルの内積
		float startDistanceOnA		= segmentA.Dot(r);			// 線分Aの方向ベクトルと、startB→startAの位置関係を表す内積
		float startDistanceOnB		= segmentB.Dot(r);			// 線分Bの方向ベクトルと、startB→startAの位置関係を表す内積

		// 分母の計算
		// この計算法は、連立方程式を解くためのもので、線分Aと線分Bのパラメータtとuを求めるために使用されます。
		float denominator = 
			segmentALengthSq * segmentBLengthSq - segmentDirectionDot * segmentDirectionDot;

		// 分母が0に近い場合、線分Aと線分Bは平行であるため、最近接点を求めることができません。
		if(Math::Abs(denominator) < Math::EPSILON)
		{
			// 線分Aの開始点から線分B上の最近接点を求める
			Vec3::Vector3 closestB	= ClosestPointOnSegment(startA, startB, endB);
			Vec3::Vector3 diffA		= startA - closestB;
			float distanceSqA		= diffA.Dot(diffA);
			
			// 線分Aの終了点から線分B上の最近接点を求める
			Vec3::Vector3 closestB2	= ClosestPointOnSegment(endA, startB, endB);
			Vec3::Vector3 diffB		= endA - closestB2;
			float distanceSqB		= diffB.Dot(diffB);

			// 線分Aの開始点と終了点から線分B上の最近接点までの距離の二乗の最小値を返す
			return Math::Min(distanceSqA, distanceSqB);
		}
		else
		{
			// 線分A上の最近接点を求めるためのパラメータtを計算
			// 計算式は、計算した分母を使って、線分A上の最近接点のパラメータtを求めるためのものです。
			float t =
				(segmentDirectionDot * startDistanceOnB - segmentBLengthSq * startDistanceOnA) / denominator;

			// 線分B上の最近接点を求めるためのパラメータuを計算
			// 計算式は、計算した分母を使って、線分B上の最近接点のパラメータuを求めるためのものです。
			float u =
				(segmentALengthSq * startDistanceOnB - segmentDirectionDot * startDistanceOnA) / denominator;

			// tとuを0.0fから1.0fの範囲にクランプ
			t = Math::Clamp(t, 0.0f, 1.0f);
			u = Math::Clamp(u, 0.0f, 1.0f);

			// 線分A上の最近接点と線分B上の最近接点を計算
			Vec3::Vector3 closestA = startA + segmentA * t;
			Vec3::Vector3 closestB = startB + segmentB * u;

			// 線分A上と線分B上の最近接点の差ベクトルを計算
			Vec3::Vector3 diff = closestA - closestB;
			return diff.Dot(diff);
		}
	}

	Vec3::Vector3 ClosestPointOnSegment(
		const Vec3::Vector3& point,
		const Vec3::Vector3& segmentStart,
		const Vec3::Vector3& segmentEnd)
	{
		// 線分のベクトルを計算
		Vec3::Vector3 segmentVector = segmentEnd - segmentStart;

		// 点から線分の開始点へのベクトルを計算
		Vec3::Vector3 pointVector = point - segmentStart;

		// 線分の長さの二乗を計算
		float segmentLengthSq = segmentVector.Dot(segmentVector);

		// 線分の長さが0に近い場合、線分の開始点を返す
		if(Math::Abs(segmentLengthSq) < Math::EPSILON){ return segmentStart; }

		// 線分の長さの二乗を計算
		float t = pointVector.Dot(segmentVector) / segmentVector.Dot(segmentVector);

		// tを0.0fから1.0fの範囲にクランプ
		t = Math::Clamp(t, 0.0f, 1.0f);

		// 線分上の最近接点を計算
		return segmentStart + segmentVector * t;
	}
}