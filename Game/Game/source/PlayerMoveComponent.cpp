#include "PlayerMoveComponent.h"
#include "Character.h"
#include "InputManager.h"

namespace
{
	constexpr float MOVE_SPEED = 5.0f;	// 移動速度
}

void PlayerMoveComponent::Update(Character& character)
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);

	// パッドが接続されている場合
	if(pad_1.IsConnected())
	{
		float moveX = static_cast<float>(pad_1.GetLeftStickX());	// 左スティックを移動ベクトルのX成分にする
		float moveZ = static_cast<float>(pad_1.GetLeftStickY());	// 左スティックを移動ベクトルのZ成分にする
		m_moveVector = VGet(moveX, 0.0f, moveZ);					// Y成分は0にして、移動ベクトルを作成
		m_moveVector = VScale(m_moveVector, MOVE_SPEED);			// 移動ベクトルを移動速度でスケーリングする
	}
	// パッドが接続されていない場合
	else
	{
		// 移動ベクトルを0にする
		m_moveVector = VGet(0.0f, 0.0f, 0.0f);
	}
}