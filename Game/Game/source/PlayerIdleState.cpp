#include "PlayerIdleState.h"
#include "Player.h"
#include "PlayerAnimationComponent.h"

void PlayerIdleState::Enter(Player& owner)
{
	// アイドルアニメーションを再生する
	auto playerAnimComp = owner.GetComponent<PlayerAnimationComponent>();
	if(playerAnimComp) { playerAnimComp->PlayAnimIdle(); }
}

void PlayerIdleState::Update(Player& owner)
{
	auto playerAnimComp = owner.GetComponent<PlayerAnimationComponent>();
	if(playerAnimComp) { playerAnimComp->PlayAnimIdle(); }
}

void PlayerIdleState::Exit(Player& owner)
{

}