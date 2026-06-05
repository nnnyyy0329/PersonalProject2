#include "Player.h"
#include "Server/ResourceServer.h"
#include "InputManager.h"
#include "ActionMove.h"
#include "HealthComponent.h"
#include "PlayerMoveComponent.h"
#include "DxLibAnimationComponent.h"

Player::Player() = default;

Player::~Player() = default;

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	// プレイヤーの体力コンポーネントを追加
	AddComponent(std::make_unique<HealthComponent<Character>>(200.0f));

	// プレイヤーの移動アクションを追加
	AddComponent(std::make_unique<PlayerMoveComponent>());

	// プレイヤーのアニメーションの追加登録
	using AnimComp = DxLibAnimationComponent<Character>;
	auto animComponent = std::make_unique<AnimComp>();
	animComponent->RegisterAnimation("Nchange_attack_00", m_data.handle);
	animComponent->RegisterAnimation("Nchange_attack_01", m_data.handle);
	animComponent->RegisterAnimation("Nchange_attack_02", m_data.handle);
	animComponent->RegisterAnimation("Nchange_attack_03", m_data.handle);
	animComponent->RegisterAnimation("Nchange_attack_04", m_data.handle);
	animComponent->RegisterAnimation("player_idle_01", m_data.handle);
	animComponent->RegisterAnimation("player_walk_01", m_data.handle);
	animComponent->RegisterAnimation("player_jog_01", m_data.handle);

	// アニメーションコンポーネントを追加
	AddComponent(std::move(animComponent));

	// 初期状態のアクションとして移動を設定
	SetAction(std::make_unique<ActionMove>());

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
	if(InputManager::GetInstance().GetPad(0).isTrigger(PadButton::X))
	{
		auto healthComponent = GetComponent<HealthComponent<Character>>();

		if(healthComponent)
		{
			healthComponent->ApplyDamage(10.0f);
		}
	}

	// 基底クラスの更新処理を呼び出す
	Character::Update();
}