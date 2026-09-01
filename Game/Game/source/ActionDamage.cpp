#include "ActionDamage.h"
#include "Character.h"
#include "GravityComponent.h"

namespace
{
	// ノックバックの減衰率
	constexpr float KNOCKBACK_DECAY_RATE = 0.9f;
}

void ActionDamage::Update(Character& character)
{
	// ノックバックを更新する
	UpdateKnockback(character);

	// タイマーを更新する
	UpdateTimer(character);
}

void ActionDamage::UpdateKnockback(Character& character)
{
	ObjectData data = character.GetObjectData();

	// ノックバックのベクトルを取得し、Y方向の成分を0にして水平移動のみを適用する
	Vec3::Vector3 knockback = m_knockBackVelocity;
	knockback.SetY(0.0f);

	data.pos += knockback;

	character.SetObjectData(data);

	// ノックバックのベクトルを減衰させる
	m_knockBackVelocity = m_knockBackVelocity * KNOCKBACK_DECAY_RATE;
}

void ActionDamage::UpdateTimer(Character& character)
{
	// タイマーを減少させる
	m_timer -= 1.0f;

	if(m_timer <= 0.0f)
	{
		// アクションを終了する
		m_isFinished = true;
	}
}