#include "PlayerDamageState.h"
#include "Player.h"
#include "PlayerAnimationComponent.h"

void PlayerDamageState::Enter(Player& owner)
{
	// ダメージアニメーションを再生
	auto* playerAnimComp = owner.GetComponent<PlayerAnimationComponent>();
	if(playerAnimComp) { playerAnimComp->PlayAnimDamage(); }
}

void PlayerDamageState::Update(Player& owner)
{

}

void PlayerDamageState::Exit(Player& owner)
{

}