#include "Map.h"

Map::Map()
{
	
}

Map::~Map()
{
	// マップのグラフィックハンドル解放
	Terminate();
}

bool Map::Initialize()
{

	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_mapData.handle = rs->GetHandle("Map");

	return true;
}

bool Map::Terminate()
{
	// マップのグラフィックハンドル解放
	MV1DeleteModel(m_mapData.handle);

	return true;
}

MapData& Map::GetMapData()
{
	// マップデータを返す
	return m_mapData;
}
