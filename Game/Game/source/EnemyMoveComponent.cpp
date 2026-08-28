#include "EnemyMoveComponent.h"
#include "Character.h"
#include "InputManager.h"

namespace
{
	constexpr float MOVE_SPEED = 1.5f;	// 移動速度
}

void EnemyMoveComponent::MoveToTarget(const Vec3::Vector3& targetPos)
{
	// 現在の位置を取得
	Vec3::Vector3 currentPos = GetOwner()->GetObjectData().pos;

	// 目標位置への方向ベクトルを計算
	Vec3::Vector3 direction = targetPos - currentPos;
	direction.SetY(0.0f);

	// 方向ベクトルを正規化
	float length = direction.Length();
	if(length > 0.0f){ direction = direction * (1.0f / length); }

	// 移動ベクトルを設定
	m_moveVector = direction * MOVE_SPEED;
}