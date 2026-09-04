#include "EnemyBehaviorTree.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyMoveState.h"
#include "EnemyMoveComponent.h"
#include "EnemyDamageState.h"
#include "EnemyDetectionComponent.h"
#include "EnemyAttackComponent.h"
#include "ActionDamage.h"
#include "EnemyAttackState.h"
#include "ActionAttack.h"

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

	// 現在のアクションが攻撃の場合は移動をしない
	if(owner.IsCurrentAction<ActionAttack>())
	{
		return;
	}

	// 移動できるか考える
	ThinkMove(owner);
}

void EnemyBehaviorTree::ThinkMove(Enemy& owner)
{
	// 敵の検知コンポーネントと移動コンポーネントを取得
	auto* detection = owner.GetComponent<EnemyDetectionComponent>();
	auto* moveComp = owner.GetComponent<EnemyMoveComponent>();
	auto* attackComp = owner.GetComponent<EnemyAttackComponent>();
	if(!detection || !moveComp || !attackComp){ return; }

	// ステートマシンを取得
	auto& stateMachine = owner.GetStateMachine();

	auto* target = detection->GetTarget();
	if(!target)
	{
		// ターゲットがいない場合は移動ベクトルを0にする
		moveComp->MoveToTarget(owner.GetObjectData().pos);

		if(!stateMachine.IsCurrentState<EnemyIdleState>())
		{
			// アイドルステートに遷移する
			stateMachine.ChangeState(owner, std::make_unique<EnemyIdleState>());
		}

		return;
	}

	// 距離内かつ敵の前方にいる場合だけ攻撃する
	if(detection->CanStartAttack(owner))
	{
		// 攻撃を行うために移動ベクトルを0にする
		moveComp->MoveToTarget(owner.GetObjectData().pos);

		if(attackComp->TryAttack(owner))
		{
			if(!stateMachine.IsCurrentState<EnemyAttackState>())
			{
				// 攻撃ステートに遷移する
				stateMachine.ChangeState(owner, std::make_unique<EnemyAttackState>());
			}
		}

		return;
	}

	const Vec3::Vector3 enemyPos =
		owner.GetObjectData().pos;

	const Vec3::Vector3 targetPos =
		target->GetObjectData().pos;

	// A*経路を更新する
	const bool hasPath =
		moveComp->UpdatePath(
			enemyPos,
			targetPos);

	if(hasPath)
	{
		// プレイヤーではなく、経路上の次の地点へ移動する
		moveComp->MoveToTarget(
			moveComp->GetNextPathPoint());
	}
	else
	{
		// 経路がない場合の保険
		moveComp->MoveToTarget(targetPos);
	}

	if(!stateMachine.IsCurrentState<EnemyMoveState>())
	{
		stateMachine.ChangeState(
			owner,
			std::make_unique<EnemyMoveState>());
	}

	//// 攻撃範囲内でも、背後にいる場合はターゲットへ向かうことによって向きを変える
	//moveComp->MoveToTarget(target->GetObjectData().pos);

	//if(!stateMachine.IsCurrentState<EnemyMoveState>())
	//{
	//	// 移動ステートに遷移する
	//	stateMachine.ChangeState(owner, std::make_unique<EnemyMoveState>());
	//}
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