#include "PlayerStateController.h"
#include "Player.h"
#include "PlayerMoveComponent.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"
#include "PlayerAttackState.h"
#include "ActionAttack.h"
#include "PlayerDamageState.h"
#include "ActionDamage.h"
#include "PlayerDeathState.h"
#include "HealthComponent.h"

void PlayerStateController::Update(Player& player)
{
	// プレイヤーの死亡ステートを切り替える
	ChangeDeathState(player);

	// 死亡中は他のステートへ遷移させない
	auto& stateMachine = player.GetStateMachine();
	if(stateMachine.IsCurrentState<PlayerDeathState>()) { return; }

	// プレイヤーのダメージステートを切り替える
	if(player.IsCurrentAction<ActionDamage>())
	{
		ChangeDamageState(player);
		return;
	}

	// プレイヤーの攻撃ステートを切り替える
	if(player.IsCurrentAction<ActionAttack>())
	{
		ChangeAttackState(player);
		return;
	}

	// プレイヤーの移動ステートを切り替える
	ChangeMoveState(player);
}

void PlayerStateController::ChangeMoveState(Player& player)
{
	// プレイヤーのステートマシンを取得
	auto& stateMachine = player.GetStateMachine();

	// 移動コンポーネントを取得
	auto moveComp = player.GetComponent<PlayerMoveComponent>();
	if(!moveComp) { return; }

	// 移動中なら
	if(moveComp->IsMoving())
	{
		if(stateMachine.IsCurrentState<PlayerMoveState>()) { return; }

		// 移動中の場合は移動ステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerMoveState>());
	}
	// 停止中なら
	else
	{
		if(stateMachine.IsCurrentState<PlayerIdleState>()) { return; }

		// 停止中の場合はアイドルステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerIdleState>());
	}
}

void PlayerStateController::ChangeAttackState(Player& player)
{
	// プレイヤーのステートマシンを取得
	auto& stateMachine = player.GetStateMachine();

	// 攻撃中なら
	if(player.IsCurrentAction<ActionAttack>())
	{
		if(stateMachine.IsCurrentState<PlayerAttackState>()) { return; }

		// 攻撃中の場合は攻撃ステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerAttackState>());
	}
	// 攻撃中でない場合
	else
	{
		if(stateMachine.IsCurrentState<PlayerIdleState>()) { return; }

		// 攻撃ステートからアイドルステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerIdleState>());
	}
}

void PlayerStateController::ChangeDamageState(Player& player)
{
	// プレイヤーのステートマシンを取得
	auto& stateMachine = player.GetStateMachine();

	// ダメージ中なら
	if(player.IsCurrentAction<ActionDamage>())
	{
		if(stateMachine.IsCurrentState<PlayerDamageState>()) { return; }

		// ダメージ中の場合はダメージステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerDamageState>());
	}
	// ダメージ中でない場合
	else
	{
		if(stateMachine.IsCurrentState<PlayerIdleState>()) { return; }

		// ダメージステートからアイドルステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerIdleState>());
	}
}

void PlayerStateController::ChangeDeathState(Player& player)
{
	// プレイヤーのステートマシンを取得
	auto& stateMachine = player.GetStateMachine();

	// 体力コンポーネントを取得
	auto healthComp = player.GetComponent<HealthComponent<Character>>();
	if(!healthComp) { return; }

	// 体力が0以下の場合は死亡ステートに遷移する
	bool isDead = healthComp->IsDead();
	if(isDead)
	{
		if(stateMachine.IsCurrentState<PlayerDeathState>()) { return; }

		// 死亡ステートに遷移する
		stateMachine.ChangeState(player, std::make_unique<PlayerDeathState>());
	}
}