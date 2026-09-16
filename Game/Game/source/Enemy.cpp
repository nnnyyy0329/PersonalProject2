#include "Enemy.h"
#include "Server/ResourceServer.h"
#include "ActionMove.h"
#include "HealthComponent.h"
#include "DxLibAnimationComponent.h"
#include "EnemyAnimationComponent.h"
#include "CollisionComponent.h"
#include "EnemyDamageComponent.h"
#include "EnemyDebugParamCompnent.h"
#include "EnemyDebugColComponent.h"
#include "EnemyMoveComponent.h"
#include "EnemyIdleState.h"
#include "EnemyRotComponent.h"
#include "GravityComponent.h"
#include "EnemyDetectionComponent.h"
#include "EnemyAttackComponent.h"
#include "EnemyDeathState.h"

namespace
{
	// カプセルの上端のオフセット
	const Vec3::Vector3 CAPSULE_TOP_OFFSET = { 0.0f, 80.0f, 0.0f };

	// カプセルの下端のオフセット
	const Vec3::Vector3 CAPSULE_BOTTOM_OFFSET = { 0.0f, 30.0f, 0.0f };

	// カプセルの半径
	constexpr float CAPSULE_RADIUS = 30.0f;
}

bool Enemy::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	if(!rs) { return false; }

	const int enemyHandle = rs->GetHandle("Enemy");
	if(enemyHandle == -1) { return false; }

	// 敵モデルの設定
	m_data.handle = MV1DuplicateModel(enemyHandle);
	if(m_data.handle == -1) { return false; }

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();
	
	// 初期カプセルコリジョン半径
	m_charColData.capsule.radius = CAPSULE_RADIUS;

	// 基底クラスの初期化処理を呼び、全てのコンポーネントを初期化する
	Character::Initialize();

	// 初期ステートに変更
	m_stateMachine.ChangeState(*this, std::make_unique<EnemyIdleState>());

	// ハンドルが有効かどうか
	return m_data.handle != -1;
}

bool Enemy::Terminate()
{
	if(m_data.handle != -1)
	{
		MV1DeleteModel(m_data.handle);
		m_data.handle = -1;
	}

	return true;
}

void Enemy::Update(const GameContext& gameContext)
{
	// カプセルコリジョンの位置を更新
	m_charColData.capsule.start = GetObjectData().pos + CAPSULE_TOP_OFFSET;
	m_charColData.capsule.end = GetObjectData().pos + CAPSULE_BOTTOM_OFFSET;

	auto animComp = GetComponent<EnemyAnimationComponent>();
	if(!animComp) { return; }

	// 死亡ステートかつ、死亡アニメーションの再生が終了したなら、すべての更新処理を止める
	bool isDeadState = m_stateMachine.IsCurrentState<EnemyDeathState>();
	if(isDeadState && animComp->IsFinishedAnim()) { return; }

	Character::UpdateComponents(gameContext);

	// 次に行うステートを決定する
	m_behaviorTree.Think(*this);

	// ステートの更新処理を呼び出す
	m_stateMachine.Update(*this);

	// 基底クラスの更新処理を呼び出す
	Character::UpdateActions();
}

void Enemy::SetUpComponents()
{
	// 体力コンポーネントを追加
	AddComponent(std::make_unique<HealthComponent<Character>>(300.0f));

	// アニメーション管理コンポーネントを追加
	AddComponent(std::make_unique<DxLibAnimationComponent<Character>>());

	// 敵のアニメーション管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyAnimationComponent>());

	// 当たり判定コンポーネントを追加
	AddComponent(std::make_unique<CollisionComponent<Character>>());

	// 敵のダメージ管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyDamageComponent>());

	// デバッグパラメータコンポーネントを追加
	AddComponent(std::make_unique<EnemyDebugParamComponent>());

	// デバッグコリジョンコンポーネントを追加
	AddComponent(std::make_unique<EnemyDebugColComponent>());

	// 敵の移動管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyMoveComponent>());

	// 敵の回転管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyRotComponent>());

	// 重力コンポーネントを追加
	AddComponent(std::make_unique<GravityComponent<Character>>(0.25f));

	// 敵の検知管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyDetectionComponent>());

	// 敵の攻撃管理コンポーネントを追加
	AddComponent(std::make_unique<EnemyAttackComponent>());
}

void Enemy::SetUpActions()
{
	// 初期状態のアクションとして移動を設定
	SetAction(std::make_unique<ActionMove>());
}

std::unique_ptr<ICharacterAction> Enemy::CreateDefaultAction()
{	
	// デフォルトのアクションとして移動を返す
	return std::make_unique<ActionMove>();
}

bool Enemy::IsDead() const
{
	// 体力コンポーネントを取得
	auto healthComp = GetComponent<HealthComponent<Character>>();
	if(!healthComp) { return true; }

	// 死亡判定を行う
	bool isDead = healthComp->IsDead();
	bool isDeadState = m_stateMachine.IsCurrentState<EnemyDeathState>();
	bool isFinishedDeadAnim = false;
	if(isDeadState)
	{
		auto animComp = GetComponent<EnemyAnimationComponent>();
		if(!animComp) { return false; }
		
		// 死亡アニメーションの再生が終了しているかを判定する
		isFinishedDeadAnim = animComp->IsFinishedAnim();
	}

	// 体力が0以下かつ、死亡アニメーションの再生が終了している場合のみ死亡と判定する
	return isDead && isFinishedDeadAnim;
}