#pragma once
#include "DamageData.h"
#include "DxLib.h"

/// @brief 被弾情報構造体
struct DamageInfo
{
	DamageData damageData;	// 被弾性能

	VECTOR hitDirection;	// ヒット方向
};