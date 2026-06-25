#include "DebugManager.h"
#include "InputManager.h"

DebugManager& DebugManager::GetInstance()
{
	static DebugManager instance;
	return instance;
}

void DebugManager::Update()
{
	auto& input = InputManager::GetInstance();

	// Aボタンを押しながら、Bボタンでデバッグモードの切り替え
	if(input.GetPad(0).isHold(PadButton::A) && input.GetPad(0).isTrigger(PadButton::B))
	{
		// デバッグモードの切り替え
		ToggleDebugMode();
	}
}

void DebugManager::Render()
{
	if(!IsDebugMode()) { return; }

	// FPSの描画
	m_debugFps.Render();

	// デバッグパラメーターの描画
	m_debugParameter.Render(1500, 10);

	// デバッグ当たり判定の描画
	m_debugCollision.Render();

}