#include "ObjectRenderSystem.h"
#include "DxLib.h"
#include "VectorConverter/VectorConverter.h"

bool ObjectRenderSystem::Initialize()
{
	// シャドウマップ描画クラスの初期化
	if(!m_shadowMapRenderer.Initialize()) { return false; }

	return true;
}

bool ObjectRenderSystem::Terminate()
{
	// シャドウマップ描画クラスの終了処理
	if(!m_shadowMapRenderer.Terminate()) { return false; }

	return true;
}

void ObjectRenderSystem::BeginRender()
{
	// 3D基本設定
	{
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}

	// シャドウマップ有効化
	{
		SetShadowMap();
	}
}

void ObjectRenderSystem::EndRender()
{
	m_shadowMapRenderer.DisableShadowMap();
}

void ObjectRenderSystem::ObjectRender(const ObjectData& data)
{
	if(data.handle == -1) { return; }

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
	if(mapData.mapHandle != -1)
	{
		MV1SetPosition(mapData.mapHandle, Vec::ToDxVec(mapData.pos));
		//MV1DrawModel(mapData.mapHandle);
	}

	// スカイ位置設定 & 描画
	if(mapData.skyHandle != -1)
	{
		MV1SetPosition(mapData.skyHandle, Vec::ToDxVec(mapData.pos));
		MV1DrawModel(mapData.skyHandle);
	}
}

void ObjectRenderSystem::LightRender(const Light& light)
{
	// ライト設定
	SetUseLighting(TRUE);

	// ライトデータ取得
	auto lightData = light.GetLightData();
	m_lightDirection = lightData.direction;

	// 平行ライト
	{
		SetGlobalAmbientLight(GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
		ChangeLightTypeDir(Vec::ToDxVec(m_lightDirection));
	}
}

void ObjectRenderSystem::BeginShadowRender(const Light& light)
{
	// ライトデータ取得
	const LightData& lightData = light.GetLightData();

	m_lightDirection = lightData.direction;

	// シャドウマップ描画開始
	m_shadowMapRenderer.BeginRender(Vec::ToDxVec(m_lightDirection));
}

void ObjectRenderSystem::EndShadowRender()
{
	// シャドウマップ描画終了
	m_shadowMapRenderer.EndShadowRender();
}

void ObjectRenderSystem::ObjectShadowRender(const ObjectData& data)
{
	if(data.handle == -1) { return; }

	// オブジェクト位置設定 
	MV1SetPosition(data.handle, Vec::ToDxVec(data.pos));

	// オブジェクト回転設定
	MV1SetRotationXYZ(data.handle, Vec::ToDxVec(data.rot));

	// オブジェクト描画
	MV1DrawModel(data.handle);
}

void ObjectRenderSystem::MapShadowRender(const Map& map)
{
	// マップデータ取得
	const MapData& mapData = map.GetMapData();

	// マップ位置設定 & 描画
	if(mapData.mapHandle != -1)
	{
		MV1SetPosition(mapData.mapHandle, Vec::ToDxVec(mapData.pos));
		//MV1DrawModel(mapData.mapHandle);
	}
}

void ObjectRenderSystem::SetShadowMap()
{
	// シャドウマップをセット
	m_shadowMapRenderer.SetShadowMap();
}