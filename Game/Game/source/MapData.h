#pragma once
#include "Vector/Vector3.h"

/// @brief マップデータ構造体
struct MapData
{
	Vec3::Vector3 pos;	/// マップの位置
	int mapHandle;		/// マップのグラフィックハンドル
	int skyHandle;		/// スカイのグラフィックハンドル

	MapData()
	{
		pos			= Vec3::Vector3(0.0f, 0.0f, 0.0f);
		mapHandle	= -1;
		skyHandle	= -1;
	}
};
