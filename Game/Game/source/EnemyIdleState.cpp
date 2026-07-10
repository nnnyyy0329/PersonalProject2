#include "EnemyIdleState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyIdleState::Enter(Enemy& owner)
{
	// アイドルアニメーションを再生する
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(enemyAnimComp) { enemyAnimComp->PlayAnimIdle(); }
}

void EnemyIdleState::Update(Enemy& owner)
{

}

void EnemyIdleState::Exit(Enemy& owner)
{

}