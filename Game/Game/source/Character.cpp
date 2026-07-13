#include "Character.h"

bool Character::Initialize()
{
	// すべてのコンポーネントを初期化する
	for(auto& component : m_components)
	{
		// コンポーネントの初期化関数を呼び出す
		if(!component->Initialize(*this)) { return false; }
	}

	return true;
}

bool Character::Terminate()
{
	return true;
}

void Character::Update()
{
	for(auto& component : m_components)
	{
		// コンポーネントの更新関数を呼び出す
		component->Update(*this);
	}

	if(m_currentAction)
	{
		// アクションの実行関数を呼び出す
		m_currentAction->Update(*this);

		// アクションが終了しているなら
		if(m_currentAction->IsFinished())
		{
			// 現在のアクションをリセットする
			m_currentAction.reset();
		}
	}
}

void Character::SetAction(std::unique_ptr<ICharacterAction> newAction)
{
	// 現在のアクションを新しいアクションに置き換える
	m_currentAction = std::move(newAction);
}

void Character::AddComponent(std::unique_ptr<ComponentBase> component)
{
	// 新しいコンポーネントをベクターに追加する
	m_components.push_back(std::move(component));
}