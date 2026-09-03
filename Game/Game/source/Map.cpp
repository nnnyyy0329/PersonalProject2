#include "Map.h"

#include "Server/ResourceServer.h"
#include "Server/SoundServer.h"
#include "DebugManager.h"

bool Map::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	// マップのグラフィックハンドル取得
	m_mapData.mapHandle = rs->GetHandle("Map");
	m_mapData.skyHandle = rs->GetHandle("Sky");

	// マップのコリジョンハンドル取得
	m_mapCollisionHandle = MV1SearchFrame(m_mapData.mapHandle, "dungeon_collision");

	// ステージBGMのハンドル取得、再生
	m_stageBgm = SoundServer::GetInstance()->Play("BGM_Stage", DX_PLAYTYPE_BACK);

	// 立方体のテクスチャハンドルを立方体形状クラスに設定
	int mapCubeTextureHandle = rs->GetHandle("CubeTexture");
	if(mapCubeTextureHandle != -1)
	{
		m_primitiveShapeCube.SetTextureHandle(mapCubeTextureHandle);
		m_primitiveShapeCube.CreateCube(Vec3::Vector3(0.0f, 50.0f, 0.0f), 100.0f);
		m_primitiveShapeCube.AddCube(Vec3::Vector3(100.0f, 50.0f, 0.0f), 100.0f);
	}

	return true;
}

bool Map::Terminate()
{
	// グラフィックハンドル解放
	MV1DeleteModel(m_mapData.mapHandle);
	MV1DeleteModel(m_mapData.skyHandle);
	
	// コリジョンハンドル解放
	MV1DeleteModel(m_mapCollisionHandle);

	return true;
}

void Map::Update()
{
	// デバッグクラスのインスタンスを取得
	auto& debugManager = DebugManager::GetInstance();
	auto& debugCollision = debugManager.GetDebugCollision();

	// デバッグモードの場合
	if(debugManager.IsDebugMode())
	{
		// コリジョンを表示
		debugCollision.AddColItem([this]()
			{
				MV1SetFrameVisible(m_mapData.mapHandle, m_mapCollisionHandle, FALSE);
			});
	}
	// デバッグモードでない場合
	else
	{
		// コリジョンを非表示
		debugCollision.AddColItem([this]()
			{
				MV1SetFrameVisible(m_mapData.mapHandle, m_mapCollisionHandle, FALSE);
			});
	}
}

void Map::Render()
{
	// 立方体の描画
	m_primitiveShapeCube.Render();
}