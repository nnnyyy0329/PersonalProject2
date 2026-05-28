#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

bool Character::Initialize()
{
	return true;
}

bool Character::Terminate()
{
	return true;
}

void Character::Update()
{
	if(m_currentAction)
	{
		m_currentAction->Execute(*this);
	}
}

void Character::SetAction(std::unique_ptr<ICharacterAction> newAction)
{
	// 現在のアクションを新しいアクションに置き換える
	m_currentAction = std::move(newAction);
}