#include "PlayerInputComponent.h"

void PlayerInputComponent::Update(Character& owner)
{
	// 攻撃コマンドを実行する
	m_attackCommand.Execute(owner);
}
