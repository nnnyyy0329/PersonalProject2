#include "Player.h"
#include "InputManager.h"
#include "ActionMove.h"

Player::Player() = default;

Player::~Player() = default;

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	// 初期状態のアクションとして移動を設定
	SetAction(std::make_unique<ActionMove>());

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
	// 基底クラスの更新処理を呼び出す
	Character::Update();
}