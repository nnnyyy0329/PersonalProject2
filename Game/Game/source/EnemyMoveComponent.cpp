#include "EnemyMoveComponent.h"
#include "Character.h"
#include "InputManager.h"




/* 今だけプレイヤーと同じ処理で確かめる */
namespace
{
	constexpr float MOVE_SPEED = 1.5f;	// 移動速度
}
void EnemyMoveComponent::Update(Character& character)
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(1);

	// パッドが接続されている場合
	if(pad_1.IsConnected())
	{
		float moveX = static_cast<float>(pad_1.GetLeftStickX());	// 左スティックを移動ベクトルのX成分にする
		float moveZ = static_cast<float>(pad_1.GetLeftStickY());	// 左スティックを移動ベクトルのZ成分にする
		m_moveVector.Set(moveX, 0.0f, moveZ);						// Y成分は0にして、移動ベクトルを作成

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
/* 今だけプレイヤーと同じ処理で確かめる */


