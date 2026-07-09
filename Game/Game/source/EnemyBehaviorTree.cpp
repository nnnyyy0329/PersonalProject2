#include "EnemyBehaviorTree.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyMoveComponent.h"

std::unique_ptr<IState<Enemy>> EnemyBehaviorTree::Think(Enemy& owner)
{
	// 現在のステートを取得
	auto currentState = owner.GetStateMachine().GetCurrentState();
	if(!currentState) { return std::make_unique<EnemyIdleState>(); }

	// 移動できる場合は移動ステートに遷移する
	auto moveComp = owner.GetComponent<EnemyMoveComponent>();
	if(moveComp && moveComp->CanMove())
	{
		// 仮でアイドルステートに遷移。移動しているときにアイドルモーションをしていたら成功している。
		return std::make_unique<EnemyIdleState>();
	}


	// 遷移しない場合はnullptrを返す
	return nullptr;
}