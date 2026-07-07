#pragma once
#include "Vector/Vector3.h"

/// @brief 当たり判定の形状を表す列挙型
enum class ShapeType
{
	NONE,
	SPHERE,	///< 球形
	BOX,	///< 立方体
	CAPSULE	///< カプセル
};

/// @brief 当たり判定のデータ構造体
struct CollisionData
{
	ShapeType shape;			/// 当たり判定の形状
	Vec3::Vector3 size;			/// 当たり判定のサイズ
	Vec3::Vector3 topOffset;	/// カプセル形状の上端のオフセット
	Vec3::Vector3 bottomOffset;	/// カプセル形状の下端のオフセット
	float radius;				/// 球形の半径

	CollisionData()
	{
		shape			= ShapeType::NONE;
		size			= Vec3::Vector3(0.0f, 0.0f, 0.0f);
		topOffset		= Vec3::Vector3(0.0f, 0.0f, 0.0f);
		bottomOffset	= Vec3::Vector3(0.0f, 0.0f, 0.0f);
		radius			= 0.0f;
	}
};