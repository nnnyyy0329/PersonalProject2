#include "EnemyRotComponent.h"
#include "Character.h"
#include "EnemyMoveComponent.h"

bool EnemyRotComponent::Initialize(Character& character)
{
	// キャラクターの移動コンポーネントを取得
	m_enemyMoveComponent = character.GetComponent<EnemyMoveComponent>();
	if(!m_enemyMoveComponent) { return false; }

	return true;
}

void EnemyRotComponent::Update(Character& character, const GameContext& gameContext)
{
	m_rotVector = m_enemyMoveComponent->GetMoveVector();
}