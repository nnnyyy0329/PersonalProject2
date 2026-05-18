#pragma once
#include "DxLib.h"

/// @brief オブジェクトデータ構造体
struct ObjectData
{
	VECTOR pos; ///< オブジェクトの位置
	VECTOR rot; ///< オブジェクトの回転
	int handle;	///< オブジェクトのグラフィックハンドル

	ObjectData()
	{
		pos		= { 0.0f, 0.0f, 0.0f };
		rot		= { 0.0f, 0.0f, 0.0f };
		handle	= -1;
	}
};
