#include "PlayerStateController.h"
#include "Player.h"
#include "PlayerMoveComponent.h"
#include "PlayerMoveState.h"
#include "PlayerIdleState.h"

void PlayerStateController::Update(Player& player)
{
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