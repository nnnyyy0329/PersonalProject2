#include "ActionDamage.h"
#include "Character.h"

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

	// ノックバック方向にキャラクターを移動させる
	data.pos = VAdd(data.pos, m_knockBackVelocity);

	// 更新されたオブジェクトデータをキャラクターに設定する
	character.SetObjectData(data);

	// 減衰させる
	m_knockBackVelocity = VScale(m_knockBackVelocity, KNOCKBACK_DECAY_RATE);
}

void ActionDamage::UpdateTimer(Character& character)
{


	// タイマーを減少させる
	m_timer -= 1.0f;

	if(m_timer <= 0.0f)
	{
		// ダメージアクション終了処理
		FinishActionDamage(character);
	}
}

void ActionDamage::FinishActionDamage(Character& character)
{

}