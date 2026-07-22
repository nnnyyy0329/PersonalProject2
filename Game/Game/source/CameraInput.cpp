#include "CameraInput.h"
#include "InputManager.h"

void CameraInput::Update()
{
	// カメラの回転量を初期化
	m_rotateX = 0.0f;
	m_rotateY = 0.0f;

	// 1Pのパッド情報取得
	auto& pad = InputManager::GetInstance().GetPad(0);
	if(!pad.IsConnected()) { return; }

	//// スティックの入力がほぼゼロの場合は回転量を更新しない
	//if(pad.GetRightStickX() < 0.001f || pad.GetRightStickX() > -0.001f) { return; }
	//if(pad.GetRightStickY() < 0.001f || pad.GetRightStickY() > -0.001f) { return; }

	// 右スティックの入力を回転量に変換
	m_rotateX = static_cast<float>(pad.GetRightStickX());
	m_rotateY = static_cast<float>(pad.GetRightStickY());
}