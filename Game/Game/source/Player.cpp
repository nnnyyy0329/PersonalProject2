#include "Player.h"
#include "Server/ResourceServer.h"
#include "ActionMove.h"
#include "HealthComponent.h"
#include "PlayerMoveComponent.h"
#include "DxLibAnimationComponent.h"
#include "PlayerAnimationComponent.h"

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();

	// 基底クラスの初期化処理を呼び、全てのコンポーネントを初期化する
	Character::Initialize();

	// ハンドルが有効かどうか
	return m_data.handle != -1;
}

bool Player::Terminate()
{
	// プレイヤーのグラフィックハンドル解放
	MV1DeleteModel(m_data.handle);

	return true;
}

void Player::Update()
{
	/*if(InputManager::GetInstance().GetPad(0).isTrigger(PadButton::X))
	{
		auto healthComponent = GetComponent<HealthComponent<Character>>();

		if(healthComponent)
		{
			healthComponent->ApplyDamage(10.0f);
		}
	}*/

	// 基底クラスの更新処理を呼び出す
	Character::Update();
}

void Player::SetUpComponents()
{
	// プレイヤーの体力コンポーネントを追加
	AddComponent(std::make_unique<HealthComponent<Character>>(200.0f));

	// プレイヤーの移動コンポネントを追加
	AddComponent(std::make_unique<PlayerMoveComponent>());

	// アニメーションコンポーネントを追加
	AddComponent(std::make_unique<DxLibAnimationComponent<Character>>());

	// プレイヤーのアニメーションコンポーネントを追加
	AddComponent(std::make_unique<PlayerAnimationComponent>());
}

void Player::SetUpActions()
{
	// 移動アクションを設定
	SetAction(std::make_unique<ActionMove>());
}