#include "HitCollision.h"
#include "../math/Math.h"
#include <cmath>

namespace HitCheck
{
	bool SphereToSphere(
		const Collision::Shape::Sphere& a,
		const Collision::Shape::Sphere& b)
	{
		// 球と球の中心間の距離の二乗を計算
		Vec3::Vector3 diff = a.center - b.center;
		float distanceSq = diff.LengthSq();

		// 球の半径の合計を計算
		float radiusSum = a.radius + b.radius;

		// 球の半径の合計の二乗
		float  radiusSumSq = radiusSum * radiusSum;

		// 中心間の距離の二乗が半径の合計の二乗以下であれば衝突している
		return distanceSq <= radiusSumSq;
	}

	//bool CapsuleToCapsule(
	//	const Collision::Shape::Capsule& a,
	//	const Collision::Shape::Capsule& b)
	//{
	//	// カプセルの中心線分間の距離の二乗を計算
	//	float distanceSq = 
	//		Math::CalcSegmentToSegmentDistanceSq(a.start, a.end, b.start, b.end);

	//	// カプセルの半径の合計を計算
	//	float radiusSum = a.radius + b.radius;

	//	// 半径の合計の二乗
	//	float radiusSumSq = radiusSum * radiusSum;

	//	// 中心線分間の距離の二乗が半径の合計の二乗以下であれば衝突している
	//	return distanceSq <= radiusSumSq;
	//}

	CapsuleCollisionResult CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b)
	{
		CapsuleCollisionResult result;

		// カプセルの中心線分間の最近接点を計算
		const Math::SegmentClosestPoints closestPoints =
			Math::CalcSegmentClosestPoints(
				a.start,
				a.end,
				b.start,
				b.end);

		// カプセルの半径の合計を計算
		float radiusSum = a.radius + b.radius;

		// 衝突していない場合
		if(closestPoints.distanceSq > radiusSum * radiusSum)
		{
			// 法線ベクトルを計算する必要がないため、結果を返す
			return result;
		}

		// 最近接点間の距離を計算
		float distance = std::sqrt(closestPoints.distanceSq);

		// 衝突している場合、法線ベクトルを計算
		if(distance > Math::EPSILON)
		{
			// 最近接点間のベクトルを正規化して法線ベクトルを求める
			result.normal = 
				(closestPoints.pointB - closestPoints.pointA) / distance;
		}
		// 衝突しているが、最近接点が同じ位置にある場合
		else
		{
			// 法線ベクトルを適当に設定する
			result.normal = Vec3::Vector3(1.0f, 0.0f, 0.0f);
		}

		// 衝突していることを示すフラグと貫通深さを設定
		result.isHit = true;
		result.penetration = radiusSum - distance;

		return result;
	}
}