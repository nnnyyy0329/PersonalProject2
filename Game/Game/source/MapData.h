#pragma once
#include "Vector/Vector3.h"

namespace MapData
{
	const Vec3::Vector3 MAP_ORIGIN = Vec3::Vector3(0.0f, 0.0f, 0.0f);
	constexpr int PLANE_SIZE = 100;
	constexpr int PLANE_TILE_X = 75;
	constexpr int PLANE_TILE_Z = 75;

	/// @brief マップデータ構造体
	struct Data
	{
		Vec3::Vector3 pos;	/// マップの位置
		int mapHandle;		/// マップのグラフィックハンドル
		int skyHandle;		/// スカイのグラフィックハンドル

		Data()
		{
			pos = Vec3::Vector3(0.0f, 0.0f, 0.0f);
			mapHandle = -1;
			skyHandle = -1;
		}
	};
}
