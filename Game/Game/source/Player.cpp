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
#include "PlayerDebugParamComponent.h"
#include "PlayerDebugColComponent.h"
#include "PlayerInputComponent.h"
#include "PlayerIdleState.h"
#include "GravityComponent.h"
#include "PlayerDamageComponent.h"

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();
	



	m_charColData.capsule.radius = 30.0f;




	// 基底クラスの初期化処理を呼び、全てのコンポーネントを初期化する
	Character::Initialize();

	// 初期ステートに変更
	m_stateMachine.ChangeState(*this, std::make_unique<PlayerIdleState>());

	// ハンドルが有効かどうか
	return m_data.handle != -1;
}

bool Player::Terminate()
{
	// プレイヤーのグラフィックハンドル解放
	MV1DeleteModel(m_data.handle);

	return true;
}

void Player::Update(const GameContext& gameContext)
{




	m_charColData.capsule.start		= GetObjectData().pos + Vec3::Vector3(0.0f, 100.0f, 0.0f);
	m_charColData.capsule.end		= GetObjectData().pos;
	m_charColData.capsule.radius	= 30.0f;



	

	// 次に行うステートを決定する
	m_stateController.Update(*this);

	// ステートの更新処理を呼び出す
	m_stateMachine.Update(*this);

	// 基底クラスの更新処理を呼び出す
	Character::Update(gameContext);
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

	// デバッグパラメータコンポーネントを追加
	AddComponent(std::make_unique<PlayerDebugParamComponent>());

	// デバッグコリジョンコンポーネントを追加
	AddComponent(std::make_unique<PlayerDebugColComponent>());

	// 入力コンポーネントを追加
	AddComponent(std::make_unique<PlayerInputComponent>());

	// 重力コンポーネントを追加
	AddComponent(std::make_unique<GravityComponent<Character>>(0.25f));

	// ダメージコンポーネントを追加
	AddComponent(std::make_unique<PlayerDamageComponent>());
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