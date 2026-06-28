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
	ShapeType shape;		/// 当たり判定の形状
	VECTOR size;			/// 当たり判定のサイズ
	VECTOR topOffset;		/// カプセル形状の上端のオフセット
	VECTOR bottomOffset;	/// カプセル形状の下端のオフセット
	float radius;			/// 球形の半径

	CollisionData()
	{
		shape = ShapeType::NONE;
		size = VGet(0.0f, 0.0f, 0.0f);
		topOffset = VGet(0.0f, 0.0f, 0.0f);
		bottomOffset = VGet(0.0f, 0.0f, 0.0f);
		radius = 0.0f;
	}
};