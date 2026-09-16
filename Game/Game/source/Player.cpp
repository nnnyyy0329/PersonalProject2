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
#include "PlayerDeathState.h"

namespace
{
	// プレイヤーの初期位置
	const Vec3::Vector3 DEFAULT_POSITION		= { 600.0f, 0.0f, 0.0f };

	// プレイヤーの初期回転量
	const Vec3::Vector3 DEFAULT_ROTATION		= { 0.0f, 1.7f, 0.0f };

	// プレイヤーのカプセルコリジョンの上端のオフセット
	const Vec3::Vector3 CAPSULE_TOP_OFFSET		= { 0.0f, 100.0f, 0.0f };

	// プレイヤーのカプセルコリジョンの下端のオフセット
	const Vec3::Vector3 CAPSULE_BOTTOM_OFFSET	= { 0.0f, 30.0f, 0.0f };

	// プレイヤーのカプセルコリジョンの半径
	constexpr float CAPSULE_RADIUS				= 30.0f;
}

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	int playerHandle = rs->GetHandle("Player");
	if(playerHandle == -1) { return false; }

	// リソースサーバーのモデルを複製する
	m_data.handle = MV1DuplicateModel(playerHandle);
	if(m_data.handle == -1) { return false; }

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();
	
	// 位置と回転、カプセルコリジョン半径の初期化
	m_data.pos = DEFAULT_POSITION;
	m_data.rot = DEFAULT_ROTATION;
	m_charColData.capsule.radius = CAPSULE_RADIUS;

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
	if(m_data.handle != -1)
	{
		MV1DeleteModel(m_data.handle);
		m_data.handle = -1;
	}

	return true;
}

void Player::Update(const GameContext& gameContext)
{
	// プレイヤーのカプセルコリジョンの更新
	m_charColData.capsule.start		= GetObjectData().pos + CAPSULE_TOP_OFFSET;
	m_charColData.capsule.end		= GetObjectData().pos + CAPSULE_BOTTOM_OFFSET;

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

bool Player::IsDead() const
{
	// HPコンポーネントの取得
	auto healthComp = GetComponent<HealthComponent<Character>>();
	if(!healthComp) { return true; }

	// 死亡判定を行う
	bool isDead = healthComp->IsDead();
	bool isDeadState = m_stateMachine.IsCurrentState<PlayerDeathState>();
	bool isFinishedDeadAnim = false;
	if(isDeadState)
	{
		auto animComp = GetComponent<PlayerAnimationComponent>();
		if(!animComp) { return false; }

		// 死亡アニメーションの再生が終了しているかを判定する
		isFinishedDeadAnim = animComp->IsFinishedAnim();
	}

	// 体力が0以下かつ、死亡アニメーションの再生が終了している場合のみ死亡と判定する
	return isDead && isFinishedDeadAnim;
}