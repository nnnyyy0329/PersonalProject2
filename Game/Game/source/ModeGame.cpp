#include "ModeGame.h"
#include "FollowCamera.h"
#include "Player.h"
#include "InputManager.h"
#include "DebugManager.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	// マネージャークラスの生成
	CreateManagers();
	
	// ゲームコンテキストの初期化
	InitializeGameContext();

	// オブジェクトの初期化
	m_objectManager->Initialize();

	// カメラの生成
	CreateCamera();

	// マップの初期化
	m_map.Initialize();

	return true;
}

bool ModeGame::Terminate()
{
	base::Terminate();

	// オブジェクトの解放処理
	m_objectManager->Terminate();

	return true;
}

bool ModeGame::Process()
{
	base::Process();

	// 入力の更新
	InputManager::GetInstance().Update();

	// オブジェクトの更新処理
	m_objectManager->Update(m_gameContext);
	
	// 当たり判定の更新
	m_collisionManager->Update(m_objectManager->GetCharacters());

	// カメラマネージャーの更新
	m_cameraManager->Update();

	// マップの更新
	m_map.Update();

	// デバッグ表示の更新
	DebugManager::GetInstance().Update();

	return true;
}

bool ModeGame::Render()
{
	base::Render();

	// 描画開始
	m_objectRender.BeginRender();

	// カメラセットアップ
	m_cameraManager->SetUpCamera();

	// オブジェクトの描画
	m_objectManager->Render(m_objectRender);

	// マップの描画
	m_objectRender.MapRender(m_map);

	// ライトの描画
	m_objectRender.LightRender(m_light);

	// デバッグ表示
	DebugManager::GetInstance().Render();

	return true;
}

void ModeGame::CreateManagers()
{
	// オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>();

	// カメラマネージャーの生成
	m_cameraManager = std::make_unique<CameraManager>();

	// 当たり判定マネージャーの生成
	m_collisionManager = std::make_unique<CollisionManager>();
}

void ModeGame::CreateCamera()
{
	// プレイヤーオブジェクトの取得
	Player* player = m_objectManager->GetPlayer();

	// 追従カメラを生成
	auto followCamera = std::make_unique<FollowCamera>(player->GetObjectData());

	// プレイヤーの位置をカメラの注視点に設定
	m_cameraManager->ChangeCamera(std::move(followCamera));
}

void ModeGame::InitializeGameContext()
{
	// カメラマネージャーを設定
	m_gameContext.SetCameraManager(m_cameraManager.get());
}