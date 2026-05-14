#include "appframe.h"
#include "ModeGame.h"
#include "ObjectLogic.h"
#include "ObjectFactory.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	// オブジェクトの生成
	auto player = ObjectFactory::CreateObject(OBJECT_TYPE::PLAYER);
	m_objects.push_back(std::move(player));

	// マップの初期化
	m_map.Initialize();

	// カメラの初期化
	m_camera.Initialize();

	// オブジェクトの初期化
	for(auto& obj : m_objects) { obj->Initialize(); }

	return true;
}

bool ModeGame::Terminate() 
{
	base::Terminate();

	return true;
}

bool ModeGame::Process()
{
	base::Process();

	// オブジェクトの更新処理
	for(auto& obj : m_objects) { obj->Process(); }

	return true;
}

bool ModeGame::Render()
{
	base::Render();

	// 描画開始
	m_render.BeginRender();

	// カメラセットアップ
	m_camera.SetUpCamera();

	// オブジェクトの描画
	for(auto& obj : m_objects) { m_render.ObjectRender(obj->GetData()); }

	// マップの描画
	m_render.MapRender(m_map);

	return true;
}