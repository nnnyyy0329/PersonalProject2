#include "EnemyAttackState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyAttackState::Enter(Enemy& owner)
{
	// 攻撃アニメーションを再生する
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(enemyAnimComp) { enemyAnimComp->PlayAnimAttack(); }
}

void EnemyAttackState::Update(Enemy& owner)
{

}

void EnemyAttackState::Exit(Enemy& owner)
{

}