#include "EnemyDamageComponent.h"
#include "Character.h"
#include "ActionDamage.h"
#include "HealthComponent.h"

EnemyDamageComponent::EnemyDamageComponent()
{
	m_damageInfo.damageData.knockback = 2.0f;
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

void EnemyDamageComponent::OnDamaged(Character& owner, float newHealth, float maxHealth)
{
	owner.SetAction(std::make_unique<ActionDamage>(m_damageInfo));
}
