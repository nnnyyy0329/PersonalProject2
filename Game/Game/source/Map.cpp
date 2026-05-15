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

	// マップのグラフィックハンドル取得
	m_mapData.mapHandle = rs->GetHandle("Map");
	m_mapData.skyHandle = rs->GetHandle("Sky");

	return true;
}

bool Map::Terminate()
{
	// グラフィックハンドル解放
	MV1DeleteModel(m_mapData.mapHandle);
	MV1DeleteModel(m_mapData.skyHandle);

	return true;
}
