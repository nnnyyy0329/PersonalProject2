#include "Enemy.h"
#include "Server/ResourceServer.h"
#include "ActionMove.h"

Enemy::Enemy() = default;

Enemy::~Enemy() = default;

bool Enemy::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Enemy");

	// 初期状態のアクションとして移動を設定
	SetAction(std::make_unique<ActionMove>());

	// 基底クラスの初期化処理を呼び、全てのコンポーネントを初期化する
	Character::Initialize();

	// ハンドルが有効かどうか
	return m_data.handle != -1;
}

bool Enemy::Terminate()
{
	// 敵のグラフィックハンドル解放
	MV1DeleteModel(m_data.handle);

	return true;
}

void Enemy::Update()
{
	// 基底クラスの更新処理を呼び出す
	Character::Update();
}