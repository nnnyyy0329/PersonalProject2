#include "PlayerMoveComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "CameraBase.h"
#include "GameContext.h"

namespace
{
	constexpr float MOVE_SPEED = 5.0f;	// 移動速度
}

void PlayerMoveComponent::Update(Character& character, const GameContext& gameContext)
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);

	// パッドが接続されている場合
	if(pad_1.IsConnected())
	{
		// 左スティックの入力値を取得
		float moveX = static_cast<float>(pad_1.GetLeftStickX());
		float moveZ = static_cast<float>(pad_1.GetLeftStickY());

		// カメラマネージャーから現在のカメラを取得
		auto& m_cameraManager = gameContext.GetCameraManager();
		auto& camera = m_cameraManager.GetCurrentCamera();

		// カメラの前方向と右方向を取得
		Vec3::Vector3 forward = camera->GetHorizontalForward();
		Vec3::Vector3 right = camera->GetHorizontalRight();

		// カメラの向きに合わせて移動ベクトルを作成
		m_moveVector = right * moveX + forward * moveZ;
		m_moveVector.SetY(0.0f);

		// 方向を正規化
		float length = m_moveVector.Length();
		if(length > 0.0f)
		{
			// 移動ベクトルを正規化
			m_moveVector = m_moveVector * (1.0f / length);

			// 移動速度でスケーリング
			m_moveVector = m_moveVector * MOVE_SPEED;
		}
	}
	// パッドが接続されていない場合
	else
	{
		// 移動ベクトルを0にする
		m_moveVector = Vec3::Vector3(0.0f, 0.0f, 0.0f);
	}
}