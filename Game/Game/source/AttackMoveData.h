#pragma once
#include "AttackPhaseData.h"

/// @brief 攻撃移動データ構造体
struct AttackMoveData
{
	AttackPhase movePhase;	// 移動する攻撃のフェーズ
	float moveSpeed;		// 移動速度
	float moveTime;			// 移動時間

	AttackMoveData()
	{
		movePhase = AttackPhase::NONE;
		moveSpeed = 0.0f;
		moveTime = 0.0f;
	}
};