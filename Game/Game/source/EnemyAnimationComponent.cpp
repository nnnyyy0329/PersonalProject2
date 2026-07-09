#include "Character.h"
#include "EnemyAnimationComponent.h"
#include "DxLibAnimationComponent.h"
#include "ActionDamage.h"

bool EnemyAnimationComponent::Initialize(Character& owner)
{
	// アニメーション管理コンポーネントの取得
	m_animationComponent = owner.GetComponent<DxLibAnimationComponent<Character>>();
	if(m_animationComponent == nullptr) { return false; }

	// 敵のアニメーションを登録
	RegisterEnemyAnimations(owner);

	// 初期アニメーション（アイドルアニメーション）を再生
	PlayAnimIdle();

	return true;
}

void EnemyAnimationComponent::Update(Character& owner)
{
	// ダメージを受けたときのアニメーションを切り替える
	AnimationChangeByDamage(owner);
}

void EnemyAnimationComponent::RegisterEnemyAnimations(Character& owner)
{
	// アニメーション管理コンポーネントが存在しない場合は登録できない
	if(m_animationComponent == nullptr) { return; }

	// 敵のアニメーションを登録
	m_animationComponent->RegisterAnimation("enemy_idle_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("enemy_walk_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("enemy_damage_00", owner.GetModelHandle());
}

void EnemyAnimationComponent::AnimationChangeByDamage(Character& owner)
{
	// ダメージを受けている場合
	if(owner.IsCurrentAction<ActionDamage>())
	{
		// ダメージアクション中はダメージアニメーションを再生
		m_animationComponent->PlayAnimation("enemy_damage_00", {});
	}
}

void EnemyAnimationComponent::PlayAnimIdle()
{
	// アイドルアニメーションを再生
	m_animationComponent->PlayAnimation("enemy_idle_01", {});
}