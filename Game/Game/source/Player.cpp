#include "Player.h"

Player::Player()
{

}

Player::~Player()
{
	Terminate();
}

bool Player::Initialize()
{
	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();
	m_data.handle = rs->GetHandle("Player");

	return true;
}

bool Player::Terminate()
{
	// プレイヤーのグラフィックハンドル解放
	MV1DeleteModel(m_data.handle);

	return true;
}

void Player::Update()
{
	// プレイヤーを前方に移動させる
	m_data.pos = VAdd(m_data.pos, VGet(0.0f, 0.0f, 1.0f));	
}