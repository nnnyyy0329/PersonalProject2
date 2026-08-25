#include "ObjectRenderSystem.h"
#include "DxLib.h"
#include "VectorConverter/VectorConverter.h"

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
	MV1SetPosition(data.handle, Vec::ToDxVec(data.pos));

	// オブジェクト回転設定
	MV1SetRotationXYZ(data.handle, Vec::ToDxVec(data.rot));

	// オブジェクト描画
	MV1DrawModel(data.handle);
}

void ObjectRenderSystem::MapRender(const Map& map)
{
	// マップデータ取得
	const MapData& mapData = map.GetMapData();

	// マップ位置設定 & 描画
	MV1SetPosition(mapData.mapHandle, Vec::ToDxVec(mapData.pos));
	MV1DrawModel(mapData.mapHandle);

	// スカイ位置設定 & 描画
	MV1SetPosition(mapData.skyHandle, Vec::ToDxVec(mapData.pos));
	MV1DrawModel(mapData.skyHandle);
}

void ObjectRenderSystem::LightRender(const Light& light)
{
	// ライト設定
	SetUseLighting(TRUE);

	// ライトデータ取得
	auto lightData = light.GetLightData();
	lightData.direction = Vec3::Vector3(-1.0f, -1.0f, 0.5f);

	// 平行ライト
	{
		SetGlobalAmbientLight(GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
		ChangeLightTypeDir(Vec::ToDxVec(lightData.direction));
	}
}