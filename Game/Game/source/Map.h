#pragma once
#include "appframe.h"

/// @brief マップデータ構造体
struct MapData
{
	VECTOR pos;	/// @brief マップの位置
	int handle;	/// @brief マップのグラフィックハンドル

	/// @brief マップデータコンストラクタ
	MapData()
	{
		pos = { 0.0f, 0.0f, 0.0f };
		handle = -1;
	}
};

/// @brief マップクラス
class Map
{
public:

	Map();
	virtual ~Map();

	/* 基本関数 */

	/// @brief 初期化関数
	bool Initialize();	

	/// @brief 終了関数
	bool Terminate();	


	/* 内部関数 */

	/// @brief マップデータ取得
	/// 
	/// @return マップデータ
	const MapData& GetMapData() const { return m_mapData; }

protected:

	MapData m_mapData;	/// @brief マップデータ

};

