#include "PlayerDeathState.h"
#include "Player.h"
#include "PlayerAnimationComponent.h"

void PlayerDeathState::Enter(Player& owner)
{
	// アニメーションコンポーネントを取得
	auto animationComp = owner.GetComponent<PlayerAnimationComponent>();
	if(animationComp) { animationComp->PlayAnimDeath(); }
}

void PlayerDeathState::Update(Player& owner)
{

}

void PlayerDeathState::Exit(Player& owner)
{

}