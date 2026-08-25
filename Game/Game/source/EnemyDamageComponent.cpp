#include "EnemyDamageComponent.h"
#include "Character.h"
#include "ActionDamage.h"
#include "HealthComponent.h"
#include "GravityComponent.h"

EnemyDamageComponent::EnemyDamageComponent()
{
	m_damageInfo.damageData.knockbackSpeed = 1.7f;
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

void EnemyDamageComponent::OnDamaged(Character& owner, const DamageInfo& damageInfo)
{
	auto gravity = owner.GetComponent<GravityComponent<Character>>();
	if(gravity)
	{
		// ダメージ情報からノックバック方向を取得
		const Vec3::Vector3& direction = damageInfo.damageData.moveDirection;

		// 上方向ノックバックを初速度として設定する
		gravity->SetVelocityY(direction.GetY() * damageInfo.damageData.knockbackSpeed);
	}

	// ダメージアクションを設定
	owner.SetAction(std::make_unique<ActionDamage>(damageInfo));
}
