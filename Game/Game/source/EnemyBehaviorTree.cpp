#include "EnemyBehaviorTree.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyMoveComponent.h"
#include "EnemyDamageState.h"
#include "EnemyDetectionComponent.h"
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
	// 敵の検知コンポーネントと移動コンポーネントを取得
	auto* detection = owner.GetComponent<EnemyDetectionComponent>();
	auto* moveComp = owner.GetComponent<EnemyMoveComponent>();
	if(!detection || !moveComp){ return; }

	auto* target = detection->GetTarget();
	if(target)
	{
		// ターゲットがいる場合はターゲットの位置に移動する
		moveComp->MoveToTarget(target->GetObjectData().pos);
	}
	else
	{
		// ターゲットがいない場合は移動ベクトルを0にする
		moveComp->MoveToTarget(owner.GetObjectData().pos);
	}

	// ステートマシンを取得
	auto& stateMachine = owner.GetStateMachine();

	// 移動している場合
	if(moveComp->IsMoving())
	{
		if(stateMachine.IsCurrentState<EnemyMoveState>()) { return; }

		// 移動できる場合は移動ステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyMoveState>());
	}
	// 移動していない場合
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

	// 現在のステートがダメージステートでない場合
	if(!stateMachine.IsCurrentState<EnemyDamageState>())
	{
		// ダメージステートに遷移する
		stateMachine.ChangeState(owner, std::make_unique<EnemyDamageState>());
	}
}