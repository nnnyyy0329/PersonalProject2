#include "EnemyMoveState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"
#include "ActionMove.h"

void EnemyMoveState::Enter(Enemy& owner)
{
	// 移動アクションを設定する
	owner.SetAction(std::make_unique<ActionMove>());

	// 移動アニメーションを再生する
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(enemyAnimComp) { enemyAnimComp->PlayAnimMove(); }
}

void EnemyMoveState::Update(Enemy& owner)
{
	// 移動アニメーションを再生する
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(enemyAnimComp) { enemyAnimComp->PlayAnimMove(); }
}

void EnemyMoveState::Exit(Enemy& owner)
{

}
