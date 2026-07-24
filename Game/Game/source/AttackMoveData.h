#pragma once

/// @brief 攻撃移動データ構造体
struct AttackMoveData
{
	float moveSpeed;	// 移動速度
	float moveTime;		// 移動時間

	AttackMoveData()
	{
		moveSpeed = 0.0f;
		moveTime = 0.0f;
	}
};