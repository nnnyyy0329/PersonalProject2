#pragma once
#include "Vector/Vector3.h"
#include "Collision/Shape/Capsule.h"

/// @brief キャラクターの当たり判定データ構造体
struct CharColData
{
	Collision::Shape::Capsule capsule;	/// キャラクターのカプセル形状
};