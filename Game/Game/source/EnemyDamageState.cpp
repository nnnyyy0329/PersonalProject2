#include "EnemyDamageState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyDamageState::Enter(Enemy& owner)
{
	// ダメージアニメーションを再生
	auto* enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(enemyAnimComp) { enemyAnimComp->PlayAnimDamage(); }
}

void EnemyDamageState::Update(Enemy& owner)
{
	
}

void EnemyDamageState::Exit(Enemy& owner)
{

}