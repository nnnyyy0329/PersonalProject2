#pragma once
#include "appframe.h"

/// @brief オブジェクトデータ構造体
struct ObjectData
{
	VECTOR pos; /// @brief オブジェクトの位置
	VECTOR rot; /// @brief オブジェクトの回転
	int handle;	/// @brief オブジェクトのグラフィックハンドル

	/// @brief コンストラクタ
	ObjectData()
	{
		pos = { 0.0f, 0.0f, 0.0f };
		rot = { 0.0f, 0.0f, 0.0f };
		handle = -1;
	}
};
