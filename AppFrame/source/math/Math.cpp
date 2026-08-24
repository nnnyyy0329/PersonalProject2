#include "Math.h"

namespace Math
{
	float Clamp(float value, float min, float max)
	{
		if(value < min) { return min; }
		if(value > max) { return max; }
		return value;
	}

	SegmentClosestPoints CalcSegmentClosestPoints(
		const Vec3::Vector3& startA,
		const Vec3::Vector3& endA,
		const Vec3::Vector3& startB,
		const Vec3::Vector3& endB)
	{
		SegmentClosestPoints result;

		//============================================================
		// 線分のベクトルを計算
		//============================================================

		// 線分Aのベクトル
		const Vec3::Vector3 segmentA = endA - startA;

		// 線分Bのベクトル
		const Vec3::Vector3 segmentB = endB - startB;

		// 線分Bの開始点から線分Aの開始点へのベクトル
		const Vec3::Vector3 r = startA - startB;

		// 線分Aの長さの二乗
		float segmentALengthSq = segmentA.Dot(segmentA);

		// 線分Bの長さの二乗
		float segmentBLengthSq = segmentB.Dot(segmentB);

		// 線分上の位置を表すパラメータ
		//
		// t = 0.0f → 線分の開始点
		// t = 1.0f → 線分の終了点
		float t = 0.0f;
		float u = 0.0f;

		//============================================================
		// 線分Aが点の場合
		//============================================================

		// 線分Aの長さが0に近い場合、
		// 線分Aは「線分」ではなく「点」として扱う
		if(segmentALengthSq < Math::EPSILON)
		{
			// 線分AはstartAという点になる
			t = 0.0f;

			// 線分Bが線分として存在する場合
			if(segmentBLengthSq >= Math::EPSILON)
			{
				// startAから線分B上の最近接点を求める
				u =
					Math::Clamp(
						r.Dot(segmentB) / segmentBLengthSq,
						0.0f,
						1.0f);
			}
		}

		//============================================================
		// 線分Bが点の場合
		//============================================================

		else if(segmentBLengthSq < Math::EPSILON)
		{
			// 線分BはstartBという点になる
			u = 0.0f;

			// startBから線分A上の最近接点を求める
			t =
				Math::Clamp(
					-r.Dot(segmentA) / segmentALengthSq,
					0.0f,
					1.0f);
		}

		//============================================================
		// A・Bどちらも線分の場合
		//============================================================

		else
		{
			//========================================================
			// 内積を計算
			//========================================================

			// 線分Aと線分Bの方向ベクトルの内積
			float segmentDirectionDot = segmentA.Dot(segmentB);

			// 線分Aの方向ベクトルと、
			// startB → startAのベクトルの内積
			float startDistanceOnA = segmentA.Dot(r);

			// 線分Bの方向ベクトルと、
			// startB → startAのベクトルの内積
			float startDistanceOnB = segmentB.Dot(r);

			//========================================================
			// 分母を計算
			//========================================================

			// AとBの最近接点を求めるための分母
			//
			// denominatorが0に近い
			// ↓
			// 線分Aと線分Bが平行に近い
			float denominator =
				segmentALengthSq * segmentBLengthSq
				- segmentDirectionDot * segmentDirectionDot;

			//========================================================
			// まず線分A側の最近接位置を決める
			//========================================================

			// AとBが平行ではない場合、
			// まずA側の最近接位置を求める
			if(Math::Abs(denominator) >= Math::EPSILON)
			{
				t = Math::Clamp(
					(segmentDirectionDot * startDistanceOnB - segmentBLengthSq * startDistanceOnA)
					/ denominator, 0.0f, 1.0f);
			}

			//========================================================
			// 決めたAの位置に対してB側の位置を求める
			//========================================================

			// tによって決まった線分A上の点に対して、
			// 線分B上のどこが一番近いかを求めるための値
			//
			// この値をsegmentBLengthSqで割ると
			// B側のパラメータuになる
			float uNumerator =
				segmentDirectionDot * t
				+ startDistanceOnB;

			//========================================================
			// B側の最近接点が線分の外側だった場合
			//========================================================

			// B側の最近接点がstartBより外側の場合
			if(uNumerator < 0.0f)
			{
				// B側の最近接点をstartBに固定
				u = 0.0f;

				// BをstartBに固定したので、
				// startBからA上の最近接点を改めて求める
				t = Math::Clamp(
						-startDistanceOnA / segmentALengthSq, 0.0f, 1.0f);
			}

			// B側の最近接点がendBより外側の場合
			else if(uNumerator > segmentBLengthSq)
			{
				// B側の最近接点をendBに固定
				u = 1.0f;

				// BをendBに固定したので、
				// endBからA上の最近接点を改めて求める
				t = Math::Clamp(
					(segmentDirectionDot - startDistanceOnA) / segmentALengthSq, 0.0f, 1.0f);
			}

			// B側の最近接点が線分Bの内部にある場合
			else
			{
				// B側のパラメータuを計算
				u = uNumerator / segmentBLengthSq;
			}
		}

		//============================================================
		// パラメータから実際の最近接点を求める
		//============================================================

		// 線分A上の最近接点
		result.pointA = startA + segmentA * t;

		// 線分B上の最近接点
		result.pointB = startB + segmentB * u;

		//============================================================
		// 最近接点同士の距離の二乗を求める
		//============================================================

		// 最近接点Aから最近接点Bへのベクトル
		const Vec3::Vector3 diff = result.pointA - result.pointB;

		// 距離の二乗を計算
		result.distanceSq = diff.Dot(diff);

		// 最近接点A・最近接点B・距離の二乗を返す
		return result;
	}

	float CalcSegmentToSegmentDistanceSq(
		const Vec3::Vector3& startA,
		const Vec3::Vector3& endA,
		const Vec3::Vector3& startB,
		const Vec3::Vector3& endB)
	{
		const SegmentClosestPoints result =
			CalcSegmentClosestPoints(
				startA, 
				endA,
				startB,
				endB);

		return result.distanceSq;
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

		// 線分上の位置を表すパラメータtを計算
		float t = pointVector.Dot(segmentVector) / segmentLengthSq;

		// tを0.0fから1.0fの範囲にクランプ
		t = Math::Clamp(t, 0.0f, 1.0f);

		// 線分上の最近接点を計算
		return segmentStart + segmentVector * t;
	}
}