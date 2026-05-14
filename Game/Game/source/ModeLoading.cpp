#include "ModeLoading.h"
#include "ModeGame.h"

bool ModeLoading::Initialize()
{
	if(!base::Initialize()) { return false; }

	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	/* ロードするリソースを登録 */

	rs->Register("Map", "res/Dungeon/Dungeon.mv1", RESOURCE_TYPE::Model, 1.0f);
	rs->Register("Player", "res/Player/SK_player_04_multimotion.mv1", RESOURCE_TYPE::Model, 1.0f);

	return true;
}

bool ModeLoading::Terminate()
{
	base::Terminate();

	return true;
}

bool ModeLoading::Process()
{
	base::Process();

	// ロード開始
	if(!m_isLoadStarted)
	{
		ResourceServer::GetInstance()->StartLoadAsync();
		m_isLoadStarted = true;
	}

	// ロード完了しているかチェック
	if(ResourceServer::GetInstance()->IsLoadComplete())	// ロード完了している場合
	{
		// ロード完了したらゲームモードに遷移
		ModeServer::GetInstance()->Add(new ModeGame(), 10, "game");
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}