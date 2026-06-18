#include "Character.h"
#include "EnemyAnimationComponent.h"
#include "DxLibAnimationComponent.h"

bool EnemyAnimationComponent::Initialize(Character& owner)
{
	// アニメーション管理コンポーネントの取得
	m_animationComponent = owner.GetComponent<DxLibAnimationComponent<Character>>();
	if(m_animationComponent == nullptr) { return false; }

	// 敵のアニメーションを登録
	RegisterEnemyAnimations(owner);

	m_animationComponent->PlayAnimation("enemy_idle_01", {});

	return true;
}

void EnemyAnimationComponent::Update(Character& owner)
{
	// 移動ベクトルに応じてアニメーションを切り替える
	//ChangeAnimByMovement(owner);
}

//void EnemyAnimationComponent::ChangeAnimByMovement(Character& owner)
//{
//	
//}

void EnemyAnimationComponent::RegisterEnemyAnimations(Character& owner)
{
	// アニメーション管理コンポーネントが存在しない場合は登録できない
	if(m_animationComponent == nullptr) { return; }

	// 敵のアニメーションを登録
	m_animationComponent->RegisterAnimation("enemy_idle_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("enemy_walk_01", owner.GetModelHandle());
	m_animationComponent->RegisterAnimation("enemy_damage_00", owner.GetModelHandle());
}
