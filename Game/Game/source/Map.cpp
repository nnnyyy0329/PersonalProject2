#include "Map.h"

#include "Server/ResourceServer.h"
#include "Server/SoundServer.h"
#include "DebugManager.h"

bool Map::Initialize()
{
	// ハンドルの初期設定
	InitializeHandle();

	// 立方体マップを作成
	//CreateCubeMap();

	// 平面マップを作成
	CreatePlaneMap();

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

	// 平面の描画
	m_primitiveShapePlane.Render();
}

void Map::InitializeHandle()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	// マップのグラフィックハンドル取得
	m_mapData.mapHandle = rs->GetHandle("Map");
	m_mapData.skyHandle = rs->GetHandle("Sky");
	if(m_mapData.mapHandle == -1 || m_mapData.skyHandle == -1) { return; }

	// マップのコリジョンハンドル取得
	m_mapCollisionHandle = MV1SearchFrame(m_mapData.mapHandle, "dungeon_collision");
	if(m_mapCollisionHandle == -1) { return; }

	// ステージBGMのハンドル取得、再生
	m_stageBgm = SoundServer::GetInstance()->Play("BGM_Stage", DX_PLAYTYPE_BACK);
	if(m_stageBgm == -1) { return; }
}

void Map::CreateCubeMap()
{
	// 立方体のテクスチャハンドルを立方体形状クラスに設定
	int mapCubeTextureHandle = ResourceServer::GetInstance()->GetHandle("CubeTexture");
	if(mapCubeTextureHandle == -1) { return; }

	m_primitiveShapeCube.SetTextureHandle(mapCubeTextureHandle);
	m_primitiveShapeCube.CreateCube(Vec3::Vector3(0.0f, 50.0f, 0.0f), Vec3::Vector3(100.0f, 100.0f, 100.0f));
	m_primitiveShapeCube.AddCube(Vec3::Vector3(100.0f, 50.0f, 0.0f), Vec3::Vector3(100.0f, 100.0f, 100.0f));
}

void Map::CreatePlaneMap()
{
	// 平面のテクスチャハンドルを平面形状クラスに設定
	int mapPlaneTextureHandle = ResourceServer::GetInstance()->GetHandle("PlaneTexture");
	if(mapPlaneTextureHandle == -1) { return; }

	// 平面形状クラスにテクスチャハンドルを設定
	m_primitiveShapePlane.SetTextureHandle(mapPlaneTextureHandle);

	// グリッド平面を作成
	m_primitiveShapePlane.CreateGridPlane(
		MapData::MAP_ORIGIN, MapData::PLANE_SIZE, MapData::PLANE_TILE_X, MapData::PLANE_TILE_Z);
}