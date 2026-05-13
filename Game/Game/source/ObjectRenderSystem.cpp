#include "ObjectRenderSystem.h"

ObjectRenderSystem::ObjectRenderSystem()
{

}

ObjectRenderSystem::~ObjectRenderSystem()
{

}

void ObjectRenderSystem::ObjectRender(const ObjectData& data)
{
	// オブジェクト位置設定 
	MV1SetPosition(data.handle, data.pos);

	// オブジェクト回転設定
	MV1SetRotationXYZ(data.handle, data.rot);
 
	// オブジェクト描画
	MV1DrawModel(data.handle);
}

void ObjectRenderSystem::MapRender(const Map& map)
{
	// マップ描画
	const MapData& mapData = map.GetMapData();

	// マップ位置設定 
	MV1SetPosition(mapData.handle, mapData.pos);

	// マップ描画
	MV1DrawModel(mapData.handle);
}