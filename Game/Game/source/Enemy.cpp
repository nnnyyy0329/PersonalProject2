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

bool Enemy::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Enemy");

	// コンポーネントの設定
	SetUpComponents();

	// アクションの設定
	SetUpActions();




	m_charColData.radius = 30.0f;




	// 基底クラスの初期化処理を呼び、全てのコンポーネントを初期化する
	Character::Initialize();

	// 初期ステートに変更
	m_stateMachine.ChangeState(*this, std::make_unique<EnemyIdleState>());

	// ハンドルが有効かどうか
	return m_data.handle != -1;
}

bool Enemy::Terminate()
{
	// 敵のグラフィックハンドル解放
	MV1DeleteModel(m_data.handle);

	return true;
}

void Enemy::Update(const GameContext& gameContext)
{



	m_charColData.top = GetObjectData().pos + Vec3::Vector3(0.0f, 80.0f, 0.0f);
	m_charColData.bottom = GetObjectData().pos;




	// 次に行うステートを決定する
	m_behaviorTree.Think(*this);

	// ステートの更新処理を呼び出す
	m_stateMachine.Update(*this);

	// 基底クラスの更新処理を呼び出す
	Character::Update(gameContext);
}

void Enemy::SetUpComponents()
{
	// 体力コンポーネントを追加
	AddComponent(std::make_unique<HealthComponent<Character>>(200.0f));

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
