#include "ModeLoading.h"

bool ModeLoading::Initialize()
{
	if(!base::Initialize()) { return false; }

	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	// ロードするリソースを登録
	rs->Register("Map", "res/Dungeon/Dungeon.mv1", RESOURCE_TYPE::Model, 1.0f);

	return true;
}

bool ModeLoading::Terminate()
{
	base::Terminate();

	return true;
}