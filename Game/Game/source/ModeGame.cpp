#include "appframe.h"
#include "ModeGame.h"
#include "ObjectLogic.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	

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

	// オブジェクトの描画
	for(auto& obj : m_objects) { m_render.ObjectRender(obj->GetData()); }

	// マップの描画
	m_render.MapRender(m_map);

	return true;
}