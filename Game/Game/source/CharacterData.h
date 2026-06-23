#pragma once
#include "DxLib.h"

/// @brief キャラクターの当たり判定データ構造体
struct CharColData
{
	VECTOR top;
	VECTOR bottom;
	float radius;

	CharColData()
	{
		top = { 0.0f, 0.0f, 0.0f };
		bottom = { 0.0f, 0.0f, 0.0f };
		radius = 0.0f;
	}
};