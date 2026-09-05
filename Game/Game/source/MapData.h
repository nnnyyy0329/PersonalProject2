#pragma once
#include "Vector/Vector3.h"
#include <vector>

namespace MapData
{
	// 
	const Vec3::Vector3 MAP_ORIGIN = Vec3::Vector3(0.0f, 0.0f, 0.0f);
	
	/// 平面のサイズと配置枚数
	constexpr int PLANE_SIZE = 100;
	constexpr int PLANE_TILE_X = 14;
	constexpr int PLANE_TILE_Z = 14;

	/// グリッドの範囲
	constexpr int GRID_MIN_X = PLANE_SIZE * -PLANE_TILE_X / 2;
	constexpr int GRID_MIN_Z = PLANE_SIZE * -PLANE_TILE_Z / 2;
	constexpr int GRID_MAX_X = PLANE_SIZE * PLANE_TILE_X / 2;
	constexpr int GRID_MAX_Z = PLANE_SIZE * PLANE_TILE_Z / 2;

	/// @brief マップデータ構造体
	struct Data
	{
		Vec3::Vector3 pos;	/// マップの位置
		int mapHandle;		/// マップのグラフィックハンドル
		int skyHandle;		/// スカイのグラフィックハンドル

		Data()
		{
			pos			= Vec3::Vector3(0.0f, 0.0f, 0.0f);
			mapHandle	= -1;
			skyHandle	= -1;
		}
	};

	/// @brief 壁のデータ構造体
	struct WallData
	{
		Vec3::Vector3 position;	// 壁の位置
		Vec3::Vector3 size;		// 壁のサイズ

		WallData(const Vec3::Vector3& wallPosition, const Vec3::Vector3& wallSize)
			: position(wallPosition), size(wallSize)
		{
		}
	};
}

namespace WallData
{
	/// @brief 初期状態の壁データを取得する
	inline std::vector<MapData::WallData> DefaultWalls()
	{
		return
		{
			MapData::WallData
			{
				Vec3::Vector3(-500.0f, 50.0f, -300.0f),
				Vec3::Vector3(10.0f, 100.0f, 400.0f)
			},
			MapData::WallData
			{
				Vec3::Vector3(-500.0f, 50.0f, 300.0f),
				Vec3::Vector3(10.0f, 100.0f, 400.0f)
			},

			MapData::WallData
			{
				Vec3::Vector3(500.0f, 50.0f, -300.0f),
				Vec3::Vector3(10.0f, 100.0f, 400.0f)
			},
			MapData::WallData
			{
				Vec3::Vector3(500.0f, 50.0f, 300.0f),
				Vec3::Vector3(10.0f, 100.0f, 400.0f)
			},

			MapData::WallData
			{
				Vec3::Vector3(0.0f, 50.0f, -500.0f),
				Vec3::Vector3(1000.0f, 100.0f, 10.0f)
			},

			MapData::WallData
			{
				Vec3::Vector3(0.0f, 50.0f, 500.0f),
				Vec3::Vector3(1000.0f, 100.0f, 10.0f)
			}
		};
	}
}
