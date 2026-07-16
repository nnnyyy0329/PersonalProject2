#pragma once
#include "Vector/Vector3.h"

/// @brief ダメージ移動データ構造体
struct HitMoveData
{
	Vec3::Vector3 moveDirection;	/// 移動方向
	float moveSpeed;				/// 移動速度
	float moveTime;					/// 移動時間

	HitMoveData()
	{
		moveDirection = Vec3::Vector3(0.0f, 0.0f, 0.0f);
		moveSpeed = 0.0f;
		moveTime = 0.0f;
	}
};