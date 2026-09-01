#include "PlayerInputComponent.h"
#include "Character.h"
#include "ActionDamage.h"

void PlayerInputComponent::Update(Character& owner, const GameContext& gameContext)
{
	// 現在のアクションがダメージアクションである場合、攻撃コマンドを実行しない
	if(owner.IsCurrentAction<ActionDamage>()){ return; }

	// 攻撃コマンドを実行する
	m_attackCommand.Execute(owner);
}
