#include "ObjectManager.h"
#include "ObjectLogic.h"
#include "ObjectRenderSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "HealthComponent.h"

bool ObjectManager::Initialize()
{
	// オブジェクトの生成
	RegisterCreators();

	// プレイヤーオブジェクトの生成
	PlayerCreate();

	// 敵オブジェクトの生成
	EnemyCreate();

	// オブジェクトの初期化
	for(auto& obj : m_objects) { obj->Initialize(); }

	// プレイヤーの初期化
	if(m_player) { m_player->Initialize(); }
	
	return true;
}

bool ObjectManager::Terminate()
{
	// オブジェクトの解放処理
	for(auto& obj : m_objects) { obj->Terminate(); }

	// プレイヤーの解放処理
	if(m_player) { m_player->Terminate(); }

	m_objects.clear();
	m_player.reset();

	return true;
}

void ObjectManager::Update(const GameContext& context)
{
	// オブジェクトの更新処理
	for(auto& obj : m_objects) { obj->Update(context); }

	// プレイヤーの更新処理
	if(m_player) { m_player->Update(context); }
}

void ObjectManager::ObjectRender(ObjectRenderSystem& renderSystem)
{
	for(auto& obj : m_objects) 
	{
		if(!obj) { continue; }

		// オブジェクト描画処理
		renderSystem.ObjectRender(obj->GetObjectData()); 
	}

	// プレイヤーの描画処理
	if(m_player) { renderSystem.ObjectRender(m_player->GetObjectData()); }
}

void ObjectManager::ShadowRender(ObjectRenderSystem& renderSystem)
{
	for(Character* character : m_characters)
	{
		if(!character) { continue; }

		// シャドウマップ描画処理
		renderSystem.ObjectShadowRender(character->GetObjectData());
	}
}

bool ObjectManager::IsDeadAllEnemy() const
{
	for(const auto& obj : m_objects)
	{
		if(!obj) { continue; }

		// 敵へのダウンキャスト
		const Enemy* enemy = dynamic_cast<const Enemy*>(obj.get());
		if(!enemy) { continue; }

		if(!enemy->IsDead()) { return false; }
	}

	return true;
}

bool ObjectManager::IsDeadPlayer() const
{
	if(!m_player) { return true; }
	return m_player->IsDead();
}

void ObjectManager::RegisterCreators()
{
	// プレイヤーの生成関数を登録
	m_objectFactory.RegisterObject("Player", []() -> std::unique_ptr<ObjectLogic> { return std::make_unique<Player>(); });
	//m_objects.emplace_back(m_objectFactory.CreateObject("Player"));

	// 敵の生成関数を登録
	m_objectFactory.RegisterObject("Enemy", []() -> std::unique_ptr<ObjectLogic> { return std::make_unique<Enemy>(); });
	//m_objects.emplace_back(m_objectFactory.CreateObject("Enemy"));
}

const std::vector<Character*>& ObjectManager::GetCharacters()
{
	// 最初にキャラクターリストをクリア
	m_characters.clear();

	// プレイヤーが存在する場合、キャラクターリストに追加する
	if(m_player){ m_characters.push_back(m_player.get()); }

	// オブジェクトリストからキャラクターを取得
	for(auto& obj : m_objects)
	{
		// ほかのキャラクターへのダウンキャスト
		Character* character = dynamic_cast<Character*>(obj.get());
		if(character){ m_characters.push_back(character); }
	}

	// キャラクターのポインタのベクターを返す
	return m_characters;
}

void ObjectManager::PlayerCreate()
{
	// プレイヤーオブジェクトの取得
	auto playerLogic = m_objectFactory.CreateObject("Player");
	if(!playerLogic) { return; }

	// Playerへのダウンキャスト
	Player* player = dynamic_cast<Player*>(playerLogic.get());
	if(player)
	{
		// 元のユニークポインタの所有権を解放
		playerLogic.release();	

		// プレイヤーのユニークポインタに所有権を移動
		m_player.reset(player);	
	}
}

void ObjectManager::EnemyCreate()
{
	for(int i = 0; i < ENEMY_ALL_NUM; ++i)
	{
		auto enemy = m_objectFactory.CreateObject("Enemy");
		if(!enemy) { continue; }

		// 敵ごとに初期位置を設定
		ObjectData data = enemy->GetObjectData();

		data.pos =
		{
			ENEMY_DEFAULT_SPAWN_X,
			0.0f,
			ENEMY_DEFAULT_SPAWN_X + (i * ENEMY_DEFAULT_SPAWN_Z),
		};

		data.rot = ENEMY_SPAWN_ROT;

		enemy->SetObjectData(data);

		// m_objects が所有権を取得
		m_objects.emplace_back(std::move(enemy));
	}
}