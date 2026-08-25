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
	// キャラクターのオブジェクトデータを取得する
	ObjectData data = character.GetObjectData();

	// 水平方向のノックバックを適用する
	Vec3::Vector3 knockback = m_knockBackVelocity;
	knockback.SetY(0.0f);

	// ノックバック方向にキャラクターを移動させる
	data.pos += knockback;

	auto  gravityComp = character.GetComponent<GravityComponent<Character>>();
	if(gravityComp)
	{
		// Y方向の速度をノックバックのY成分に設定する
		data.pos.SetY(data.pos.GetY() + gravityComp->GetVelocityY());
	}

	// 更新されたオブジェクトデータをキャラクターに設定する
	character.SetObjectData(data);

	// 減衰させる
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