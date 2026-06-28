#pragma once
#include "DxLib.h"

/// @brief マップデータ構造体
struct MapData
{
	VECTOR pos;		/// マップの位置
	int mapHandle;	/// マップのグラフィックハンドル
	int skyHandle;	/// スカイのグラフィックハンドル

	MapData()
	{
		pos			= { 0.0f, 0.0f, 0.0f };
		mapHandle	= -1;
		skyHandle	= -1;
	}
};
