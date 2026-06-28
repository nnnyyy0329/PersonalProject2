#include "Map.h"
#include "Server/ResourceServer.h"
#include "Server/SoundServer.h"

bool Map::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	// マップのグラフィックハンドル取得
	m_mapData.mapHandle = rs->GetHandle("Map");
	m_mapData.skyHandle = rs->GetHandle("Sky");



	// ステージBGMのハンドル取得、再生
	m_stageBgm = SoundServer::GetInstance()->Play("BGM_Stage", DX_PLAYTYPE_BACK);



	return true;
}

bool Map::Terminate()
{
	// グラフィックハンドル解放
	MV1DeleteModel(m_mapData.mapHandle);
	MV1DeleteModel(m_mapData.skyHandle);

	return true;
}
