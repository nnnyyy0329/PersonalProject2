#include "HitCollision.h"
#include "../math/Math.h"

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

	bool CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b)
	{
		// カプセルの中心線分間の距離の二乗を計算
		float distanceSq = 
			Math::CalcSegmentToSegmentDistanceSq(a.start, a.end, b.start, b.end);

		// カプセルの半径の合計を計算
		float radiusSum = a.radius + b.radius;

		// 半径の合計の二乗
		float radiusSumSq = radiusSum * radiusSum;

		// 中心線分間の距離の二乗が半径の合計の二乗以下であれば衝突している
		return distanceSq <= radiusSumSq;
	}
}