#include "Player.h"
#include "Server/ResourceServer.h"
#include "ActionMove.h"
#include "HealthComponent.h"
#include "PlayerMoveComponent.h"
#include "PlayerRotComponent.h"
#include "DxLibAnimationComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerAttackComponent.h"
#include "CollisionComponent.h"

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();



	m_charColData.radius = 50.0f;



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



	m_charColData.top = VAdd(GetObjectData().pos, VGet(0.0f, 100.0f, 0.0f));
	m_charColData.bottom = GetObjectData().pos;



	// 基底クラスの更新処理を呼び出す
	Character::Update();
}

void Player::SetUpComponents()
{
	// プレイヤーの体力コンポーネントを追加
	AddComponent(std::make_unique<HealthComponent<Character>>(200.0f));

	// プレイヤーの移動コンポネントを追加
	AddComponent(std::make_unique<PlayerMoveComponent>());
	
	// プレイヤーの回転コンポーネントを追加
	AddComponent(std::make_unique<PlayerRotComponent>());

	// アニメーションコンポーネントを追加
	AddComponent(std::make_unique<DxLibAnimationComponent<Character>>());

	// プレイヤーのアニメーションコンポーネントを追加
	AddComponent(std::make_unique<PlayerAnimationComponent>());

	// プレイヤーの攻撃コンポーネントを追加
	AddComponent(std::make_unique<PlayerAttackComponent>());

	// 当たり判定コンポーネントを追加
	AddComponent(std::make_unique<CollisionComponent<Character>>());
}

void Player::SetUpActions()
{
	// 移動アクションを設定
	SetAction(std::make_unique<ActionMove>());
}

std::unique_ptr<ICharacterAction> Player::CreateDefaultAction()
{
	// デフォルトのアクションは移動アクション
	return std::make_unique<ActionMove>();
}