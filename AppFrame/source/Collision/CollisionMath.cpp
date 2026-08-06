#include "CollisionMath.h"

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

		// 中心間の距離の二乗が半径の合計の二乗以下であれば衝突している
		return distanceSq <= (radiusSum * radiusSum);
	}

	bool CapsuleToCapsule(
		const Collision::Shape::Capsule& a,
		const Collision::Shape::Capsule& b)
	{

	}
}