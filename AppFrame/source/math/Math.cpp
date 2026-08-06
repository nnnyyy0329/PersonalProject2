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
		Vec3::Vector3 segmentA = endA - startA;
		Vec3::Vector3 segmentB = endB - startB;
		Vec3::Vector3 r = startA - startB;

		float a = segmentA.Dot(segmentA);
		float b = segmentA.Dot(segmentB);
		float c = segmentB.Dot(segmentB);
		float d = segmentA.Dot(r);
		float e = segmentB.Dot(r);



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
		float t = pointVector.Dot(segmentVector) / segmentVector.Dot(segmentVector);

		// tを0.0fから1.0fの範囲にクランプ
		t = Clamp(t, 0.0f, 1.0f);

		// 線分上の最近接点を計算
		return segmentStart + segmentVector * t;
	}
}