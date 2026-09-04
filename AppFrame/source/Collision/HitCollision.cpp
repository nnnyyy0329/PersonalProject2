#include "HitCollision.h"
#include "../math/Math.h"
#include <cmath>
#include <vector>

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

	CapsuleAABBCollisionResult CapsuleToAABB(
		const Collision::Shape::Capsule& capsule,
		const Math::AABB& aabb)
	{
		CapsuleAABBCollisionResult result;

		// カプセルの中心線分のX座標とZ座標を取得
		float capsuleX = capsule.start.GetX();
		float capsuleZ = capsule.start.GetZ();

		// カプセルの中心線分のY座標の最小値と最大値を取得
		float segmentMinY = Math::Min(capsule.start.GetY(), capsule.end.GetY());
		float segmentMaxY = Math::Max(capsule.start.GetY(), capsule.end.GetY());

		// AABBの最小座標と最大座標を取得
		float closestBoxX = Math::Clamp(capsuleX, aabb.min.GetX(), aabb.max.GetX());
		float closestBoxZ = Math::Clamp(capsuleZ, aabb.min.GetZ(), aabb.max.GetZ());

		// AABBのY座標の範囲内に収まるようにクランプ
		float closestBoxY = Math::Clamp(segmentMinY, aabb.min.GetY(), aabb.max.GetY());

		// カプセルの中心線分のY座標の範囲内に収まるようにクランプ
		float closestSegmentY = Math::Clamp(closestBoxY, segmentMinY, segmentMaxY);

		const Vec3::Vector3 segmentPoint(capsuleX, closestSegmentY, capsuleZ);
		const Vec3::Vector3 boxPoint(closestBoxX, closestBoxY, closestBoxZ);

		// カプセルの中心線分上の最近接点とAABB上の最近接点の差を計算
		const Vec3::Vector3 difference = segmentPoint - boxPoint;

		// 最近接点間の距離の二乗を計算
		float distanceSq = difference.Dot(difference);

		// カプセルの半径の二乗を計算
		float radiusSq = capsule.radius * capsule.radius;

		// カプセルの半径より距離が大きければ衝突していない
		if(distanceSq > radiusSq) { return result; }

		// 最近接点間の距離を計算
		float distance = std::sqrt(distanceSq);

		// 衝突している場合、法線ベクトルを計算
		if(distance > Math::EPSILON)
		{
			// AABBからカプセルを押し出す方向
			result.normal = difference / distance;

			// めり込み量
			result.penetration = capsule.radius - distance;

			result.isHit = true;

			return result;
		}

		// 6つの面との距離を計算
		float distanceLeft = capsuleX - aabb.min.GetX();
		float distanceRight = aabb.max.GetX() - capsuleX;
		float distanceFront = capsuleZ - aabb.min.GetZ();
		float distanceBack = aabb.max.GetZ() - capsuleZ;
		float distanceBottom = segmentMaxY - aabb.min.GetY();
		float distanceTop = aabb.max.GetY() - segmentMinY;

		// 最小の距離
		float minDistance = distanceLeft;

		// 最近接点感間の距離が0のときの法線ベクトルの設定
		// 初期値として、左側の面の法線ベクトルを設定
		result.normal = Vec3::Vector3(-1.0f, 0.0f, 0.0f);

		/* それぞれ6つの面の中で、最も近い面を見つけて、法線ベクトルを設定する */
		
		if(distanceRight < minDistance)
		{
			minDistance = distanceRight;

			// 右側の面の法線ベクトルを設定
			result.normal = Vec3::Vector3(1.0f, 0.0f, 0.0f);
		}
		if(distanceFront < minDistance)
		{
			minDistance = distanceFront;

			// 前側の面の法線ベクトルを設定
			result.normal = Vec3::Vector3(0.0f, 0.0f, -1.0f);
		}
		if(distanceBack < minDistance)
		{
			minDistance = distanceBack;

			// 後側の面の法線ベクトルを設定
			result.normal = Vec3::Vector3(0.0f, 0.0f, 1.0f);
		}
		if(distanceBottom < minDistance)
		{
			minDistance = distanceBottom;

			// 下側の面の法線ベクトルを設定
			result.normal = Vec3::Vector3(0.0f, -1.0f, 0.0f);
		}
		if(distanceTop < minDistance)
		{
			minDistance = distanceTop;
			
			// 上側の面の法線ベクトルを設定
			result.normal = Vec3::Vector3(0.0f, 1.0f, 0.0f);
		}

		// 中心線分が箱の内部にあるため、
		// 面までの距離に半径を加えた量を押し出す
		result.penetration = capsule.radius + minDistance;

		result.isHit = true;

		return result;
	}
}