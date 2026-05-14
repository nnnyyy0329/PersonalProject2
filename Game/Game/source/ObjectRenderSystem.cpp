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
	// マップ描画
	const MapData& mapData = map.GetMapData();

	// マップ位置設定 
	MV1SetPosition(mapData.handle, mapData.pos);

	// マップ描画
	MV1DrawModel(mapData.handle);
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