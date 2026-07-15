#include "EnemyDamageState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyDamageState::Enter(Enemy& owner)
{
	// ダメージアニメーションを再生
	auto* animComp = owner.GetComponent<EnemyAnimationComponent>();
	if(animComp) { animComp->PlayAnimDamage(); }
}

void EnemyDamageState::Update(Enemy& owner)
{
	
}

void EnemyDamageState::Exit(Enemy& owner)
{

}