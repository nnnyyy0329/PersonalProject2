#include "PlayerAttackState.h"
#include "Player.h"
#include "PlayerAnimationComponent.h"
#include "PlayerAttackComponent.h"
#include "ActionAttack.h"

void PlayerAttackState::Enter(Player& owner)
{
	// 攻撃コンポーネントを取得する
	m_playerAttackComponent = owner.GetComponent<PlayerAttackComponent>();
	if(!m_playerAttackComponent) { return; }

	// 攻撃アニメーションを再生する
	m_playerAnimationComponent = owner.GetComponent<PlayerAnimationComponent>();
	if(m_playerAnimationComponent) { m_playerAnimationComponent->PlayAnimAttack(m_playerAttackComponent->GetComboIndex()); }
}

void PlayerAttackState::Update(Player& owner)
{
	// 攻撃コンポーネントを取得する
	m_playerAttackComponent = owner.GetComponent<PlayerAttackComponent>();
	if(!m_playerAttackComponent) { return; }

	// 攻撃アニメーションを再生する
	m_playerAnimationComponent = owner.GetComponent<PlayerAnimationComponent>();
	if(m_playerAnimationComponent) { m_playerAnimationComponent->PlayAnimAttack(m_playerAttackComponent->GetComboIndex()); }
}

void PlayerAttackState::Exit(Player& owner)
{
	
}
