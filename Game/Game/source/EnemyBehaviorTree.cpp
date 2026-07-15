#include "EnemyBehaviorTree.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyMoveComponent.h"
#include "EnemyDamageState.h"
#include "ActionDamage.h"

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

	// ダメージを考える
	if(owner.IsCurrentAction<ActionDamage>())
	{
		// ダメージを考える
		ThinkDamage(owner);
		return;
	}

	// 移動を考える
	ThinkMove(owner);
}

void EnemyBehaviorTree::ThinkMove(Enemy& owner)
{
	// ステートマシンを取得
	auto& stateMachine = owner.GetStateMachine();

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

void EnemyBehaviorTree::ThinkDamage(Enemy& owner)
{
	// ステートマシンを取得
	auto& stateMachine = owner.GetStateMachine();

	// 現在のアクションがダメージアクションの場合
	if(owner.IsCurrentAction<ActionDamage>())
	{
		if(stateMachine.IsCurrentState<EnemyDamageState>()) { return; }

		// ダメージステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyDamageState>());
	}
	// 遷移しない場合
	else
	{
		if(stateMachine.IsCurrentState<EnemyIdleState>()) { return; }

		// ダメージステートからアイドルステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyIdleState>());
	}
}