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
	if(!m_objectManager->Initialize()) { return false; }

	// オブジェクト描画システムの初期化
	if(!m_objectRender.Initialize()) { return false; }

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
	if(m_objectManager) { m_objectManager->Terminate(); }

	// オブジェクト描画システムの解放処理
	if(!m_objectRender.Terminate()) { return false; }

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

	// シャドウマップ描画開始
	{
		// シャドウマップ描画開始
		m_objectRender.BeginShadowRender(m_light);

		// マップのシャドウマップ描画
		m_objectRender.MapShadowRender(m_map);

		// オブジェクトのシャドウマップ描画
		m_objectManager->ShadowRender(m_objectRender);

		// シャドウマップ描画終了
		m_objectRender.EndShadowRender();
	}

	// カメラセットアップ
	m_cameraManager->SetUpCamera();

	// 通常描画
	{
		// 描画開始
		m_objectRender.BeginRender();

		// ライトの描画
		m_objectRender.LightRender(m_light);

		// マップの描画
		m_objectRender.MapRender(m_map);

		// オブジェクトの描画
		m_objectManager->ObjectRender(m_objectRender);

		// 描画終了
		m_objectRender.EndRender();
	}	

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