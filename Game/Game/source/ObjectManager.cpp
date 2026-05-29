#include "ObjectManager.h"
#include "ObjectLogic.h"
#include "ObjectRenderSystem.h"
#include "Player.h"
#include "Enemy.h"

ObjectManager::ObjectManager() = default;

ObjectManager::~ObjectManager() = default;

bool ObjectManager::Initialize()
{
	// オブジェクトの生成
	RegisterCreators();

	// プレイヤーオブジェクトの生成
	PlayerCreate();

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

void ObjectManager::Update()
{
	// オブジェクトの更新処理
	for(auto& obj : m_objects) { obj->Update(); }

	// プレイヤーの更新処理
	if(m_player) { m_player->Update(); }
}

void ObjectManager::Render(ObjectRenderSystem& renderSystem)
{
	// オブジェクトの描画処理
	for(auto& obj : m_objects) { renderSystem.ObjectRender(obj->GetObjectData()); }

	// プレイヤーの描画処理
	if(m_player) { renderSystem.ObjectRender(m_player->GetObjectData()); }
}

void ObjectManager::RegisterCreators()
{
	// プレイヤーの生成関数を登録
	m_objectFactory.RegisterObject("Player", []() -> std::unique_ptr<ObjectLogic> { return std::make_unique<Player>(); });
	//m_objects.emplace_back(m_objectFactory.CreateObject("Player"));


	// 敵の生成関数を登録
	m_objectFactory.RegisterObject("Enemy", []() -> std::unique_ptr<ObjectLogic> { return std::make_unique<Enemy>(); });
	m_objects.emplace_back(m_objectFactory.CreateObject("Enemy"));

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