#include "ObjectRenderSystem.h"

ObjectRenderSystem::ObjectRenderSystem()
{

}

ObjectRenderSystem::~ObjectRenderSystem()
{

}

void ObjectRenderSystem::BeginRender()
{
	// 3D基本設定
	{
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}
}

void ObjectRenderSystem::EndRender()
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
	// マップデータ取得
	const MapData& mapData = map.GetMapData();

	// マップ位置設定 & 描画
	MV1SetPosition(mapData.mapHandle, mapData.pos);
	MV1DrawModel(mapData.mapHandle);

	// スカイ位置設定 & 描画
	MV1SetPosition(mapData.skyHandle, mapData.pos);
	MV1DrawModel(mapData.skyHandle);
}

void ObjectRenderSystem::LightRender(const Light& light)
{
	// ライト設定
	SetUseLighting(TRUE);

	// ライトデータ取得
	auto lightData = light.GetLightData();

	// 平行ライト
	{
		SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
		ChangeLightTypeDir(lightData.direction);
	}
}