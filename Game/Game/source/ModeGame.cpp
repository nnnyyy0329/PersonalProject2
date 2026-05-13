#include "appframe.h"
#include "ModeGame.h"
#include "ObjectLogic.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	// マップの初期化
	m_map.Initialize();

	// カメラの初期化
	m_camera.Initialize();

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

	// カメラの更新処理
	m_camera.Process();

	return true;
}

bool ModeGame::Render()
{
	base::Render();

	// オブジェクトの描画
	for(auto& obj : m_objects) { m_render.ObjectRender(obj->GetData()); }

	// マップの描画
	m_render.MapRender(m_map);

	return true;
}