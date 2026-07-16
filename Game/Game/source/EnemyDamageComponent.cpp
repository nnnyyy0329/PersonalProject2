#include "EnemyDamageComponent.h"
#include "Character.h"
#include "ActionDamage.h"
#include "HealthComponent.h"

EnemyDamageComponent::EnemyDamageComponent()
{
	m_damageInfo.damageData.knockback = 1.7f;
	m_damageInfo.damageData.hitStunTime = 30.0f;
}

bool EnemyDamageComponent::Initialize(Character& owner)
{
	// HealthComponentを取得
	auto* health = owner.GetComponent<HealthComponent<Character>>();
	if(!health) { return false; }

	// HealthComponentのオブザーバーとして登録
	health->AddObserver(this);

	return true;
}

void EnemyDamageComponent::OnDamaged(Character& owner)
{
	// ダメージアクションを設定
	owner.SetAction(std::make_unique<ActionDamage>(m_damageInfo));
}
