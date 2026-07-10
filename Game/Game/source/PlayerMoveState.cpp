#include "PlayerMoveState.h"
#include "Player.h"
#include "PlayerAnimationComponent.h"
#include "ActionMove.h"

void PlayerMoveState::Enter(Player& owner)
{
	// 移動アクションを設定する
	owner.SetAction(std::make_unique<ActionMove>());

	// 移動アニメーションを再生する
	auto playerAnimComp = owner.GetComponent<PlayerAnimationComponent>();
	if(playerAnimComp) { playerAnimComp->PlayAnimMove(); }
}

void PlayerMoveState::Update(Player& owner)
{

}

void PlayerMoveState::Exit(Player& owner)
{

}