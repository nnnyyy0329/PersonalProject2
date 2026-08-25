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

void Character::Update(const GameContext& gameContext)
{
	for(auto& component : m_components)
	{
		// コンポーネントの更新関数を呼び出す
		component->Update(*this, gameContext);
	}

	if(m_currentAction)
	{
		// アクションの実行関数を呼び出す
		m_currentAction->Update(*this);

		// アクションが終了しているなら
		if(m_currentAction->IsFinished())
		{
			// 現在のアクションをリセットする
			//m_currentAction.reset();

			// デフォルトのアクションを作成して設定する
			m_currentAction = CreateDefaultAction();
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

Vec3::Vector3 Character::GetForward() const
{
	// Y軸回転（ヨー角）を取得
	float yaw = m_data.rot.GetY();

	// 前方向ベクトルを計算
	return { -std::sin(yaw), 0.0f, -std::cos(yaw) };
}