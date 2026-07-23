/*****************************************
* file   mymath.h
* brief  クラス
* author 成田 悠真
* date	 
******************************************/

#pragma once
#include "../Vector/Vector3.h"
#include <cmath>

static const float PI = 3.1415926535f;			// 円周率
static const float DEG_TO_RAD = PI / 180.0f;	// 度からラジアンへの変換係数
static const float RAD_TO_DEG = 180.0f / PI;	// ラジアンから度への変換係数

// 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBox
(
	int x1, int y1, int w1, int h1,
	int x2, int y2, int w2, int h2
);


// 当たり判定用。2つの円が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitCircle
(
	int x1, int y1, int r1,
	int x2, int y2, int r2
);

// 当たり判定用。円と矩形が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
int IsHitBoxCircle
(
	int cx, int cy, int r,
	int x, int y, int w, int h
);

// カプセルと点の最短距離の二乗を計算
float GetCapsulePointSq(const Vec3::Vector3& point, const Vec3::Vector3& capsuleTop, const Vec3::Vector3& capsuleBottom, float capsuleRadius);

// カプセルと球の当たり判定
bool HitCheck_Capsule_Sphere(const Vec3::Vector3& capsuleTop, const Vec3::Vector3& capsuleBottom, float capsuleRadius, const Vec3::Vector3& sphereCenter, float sphereRadius);

// 点と線分の最短距離の二乗を計算
float GetPointSegmentSq(const Vec3::Vector3& point, const Vec3::Vector3& segmentStart, const Vec3::Vector3& segmentEnd);

// 円形床判定用の構造体
struct CircleFloor
{
	Vec3::Vector3 center;// 円の中心位置
	float radius;// 円の半径
	float height;// 円の高さ

	// 点が円内にあるか
	bool IsPointInside(const Vec3::Vector3& point) const;

	// 円の境界までの距離を計算
	float GetDistEdge(const Vec3::Vector3& point) const;
};