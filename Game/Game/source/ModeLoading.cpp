#include "ModeLoading.h"
#include "ModeGame.h"
#include "Server/ResourceServer.h"

bool ModeLoading::Initialize()
{
	if(!base::Initialize()) { return false; }

	// リソースサーバーのインスタンスを取得
	auto rs = ResourceServer::GetInstance();

	/* ロードするリソースを登録 */

	rs->Register("CubeTexture", "res/Texture/Groundplants1_D.jpg", RESOURCE_TYPE::Graph, 1.0f);
	rs->Register("PlaneTexture", "res/Texture/Groundplants1_D.jpg", RESOURCE_TYPE::Graph, 1.0f);

	rs->Register("Map", "res/Dungeon/Dungeon.mv1", RESOURCE_TYPE::Model, 1.0f);

	rs->Register("Player", "res/Player/SK_player_04_multimotion.mv1", RESOURCE_TYPE::Model, 1.0f);

	rs->Register("Enemy", "res/Enemy/SK_enemy_00_multimotion.mv1", RESOURCE_TYPE::Model, 1.0f);




	rs->Register("InteriorPlayerFifthAttack", "effect/InteriorPlayer/NChange_Attack.efkefc", RESOURCE_TYPE::Effect, 20.0f);




	rs->Register("EF_Attack", "effect/en_attack_test.efkefc", RESOURCE_TYPE::Effect, 20.0f);
	
	rs->Register("SE_Attack1", "sound/SE/playerAttack1.mp3", RESOURCE_TYPE::Sound, 1.0f);
	rs->Register("SE_Attack2", "sound/SE/playerAttack2.mp3", RESOURCE_TYPE::Sound, 1.0f);
	rs->Register("SE_Attack3", "sound/SE/playerAttack3.mp3", RESOURCE_TYPE::Sound, 1.0f);
	rs->Register("SE_SwingAttack", "sound/SE/SwingAttack.mp3", RESOURCE_TYPE::Sound, 1.0f);

	rs->Register("SE_enemyDamage", "sound/SE/enemyDamage.mp3", RESOURCE_TYPE::Sound, 1.0f);

	rs->Register("EF_Damage1", "effect/SChange_Hit_00.efkefc", RESOURCE_TYPE::Effect, 1.0f);
	rs->Register("EF_Damage2", "effect/en_damage_test.efkefc", RESOURCE_TYPE::Effect, 1.0f);

	rs->Register("BGM_Stage", "sound/BGM/stage_01.mp3", RESOURCE_TYPE::Sound, 1.0f);

	rs->Register("Sky", "res/SkySphere/skysphere.mv1", RESOURCE_TYPE::Model, 1.0f);

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