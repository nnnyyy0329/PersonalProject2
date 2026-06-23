#pragma once
#include "DxLib.h"

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
	ShapeType shape;	/// 当たり判定の形状
	VECTOR size;		/// 当たり判定のサイズ
	VECTOR offset;		/// 当たり判定のオフセット
	float radius;		/// 球形の半径

	CollisionData()
	{
		shape = ShapeType::NONE;
		size = VGet(0.0f, 0.0f, 0.0f);
		offset = VGet(0.0f, 0.0f, 0.0f);
		radius = 0.0f;
	}
};