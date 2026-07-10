#include "EnemyBehaviorTree.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyMoveComponent.h"

void EnemyBehaviorTree::Think(Enemy& owner)
{
	// ステートマシンを取得
	auto& stateMachine = owner.GetStateMachine();
	
	// 現在のステートがない場合
	if(!stateMachine.GetCurrentState())
	{
		// アイドルステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyIdleState>());

		return;
	}

	// 移動コンポーネントを取得して移動中かどうかを判定する
	auto* moveComp = owner.GetComponent<EnemyMoveComponent>();
	if(moveComp && moveComp->IsMoving())
	{
		if(stateMachine.IsCurrentState<EnemyMoveState>()) { return; }

		// 移動できる場合は移動ステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyMoveState>());

		return;
	}
	// 遷移しない場合
	else
	{
		if(stateMachine.IsCurrentState<EnemyIdleState>()) { return; }

		// アイドルステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyIdleState>());
	}
}
