#include "PlayerRotComponent.h"
#include "Character.h"
#include "PlayerMoveComponent.h"

bool PlayerRotComponent::Initialize(Character& character)
{
	// キャラクターの移動コンポーネントを取得
	m_playerMoveComponent = character.GetComponent<PlayerMoveComponent>();
	if(!m_playerMoveComponent) { return false; }

	return true;
}

void PlayerRotComponent::Update(Character& character, const GameContext& gameContext)
{
	m_rotVector = m_playerMoveComponent->GetMoveVector();
}