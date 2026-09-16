#include "ModeGame.h"
#include "FollowCamera.h"
#include "Player.h"
#include "Input/InputManager.h"
#include "DebugManager.h"
#include "ModeGameClear.h"
#include "ModeGameOver.h"

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	// マネージャークラスの生成
	CreateManagers();
	
	// ゲームコンテキストの初期化
	InitializeGameContext();

	// オブジェクトの初期化
	if(!m_objectManager->Initialize()) { return false; }

	// オブジェクト生成後にコンテキストにナビゲーショングリッドを設定
	m_gameContext.SetNavigationGrid(&m_map.GetNavigationGrid());

	// オブジェクト描画システムの初期化
	if(!m_objectRender.Initialize()) { return false; }

	// カメラの生成
	CreateCamera();

	// マップの初期化
	if(!m_map.Initialize()) { return false; }

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
	//InputManager::GetInstance().Update();

	// オブジェクトの更新処理
	m_objectManager->Update(m_gameContext);
	
	// 当たり判定の更新
	m_collisionManager->Update(m_objectManager->GetCharacters(), m_map.GetWallColliders());

	// カメラマネージャーの更新
	m_cameraManager->Update();

	// マップの更新
	m_map.Update();

	// ゲームクリア処理
	GameClearProcess();

	// ゲームオーバー処理
	GameOverProcess();

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

		// マップの描画
		m_map.Render();

		// オブジェクトの描画
		m_objectManager->ObjectRender(m_objectRender);

		// デバッグ用ナビゲーショングリッドの描画
		m_debugNavigationGrid.Render(m_map.GetNavigationGrid());

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
	// オブジェクトマネージャーを設定
	m_gameContext.SetObjectManager(m_objectManager.get());

	// カメラマネージャーを設定
	m_gameContext.SetCameraManager(m_cameraManager.get());
}

void ModeGame::GameClearProcess()
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return; }
	bool button = pad_1.isTrigger(PadButton::X);

	// 敵が全滅したなら
	if(m_objectManager->IsDeadAllEnemy()/* || button*/)
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);

		// ゲームオーバーモードを追加
		ModeServer::GetInstance()->Add(new ModeGameClear(), 10, "game");

		// ゲームメインを作成
		//ModeServer::GetInstance()->Add(new ModeGame(), 0, "gamemain");
	}
}

void ModeGame::GameOverProcess()
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return; }
	bool button = pad_1.isTrigger(PadButton::Y);

	// プレイヤーが死亡したなら
	if(m_objectManager->IsDeadPlayer() || button)
	{
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);

		// ゲームオーバーモードを追加
		ModeServer::GetInstance()->Add(new ModeGameOver(), 10, "game");

		// ゲームメインを作成
		//ModeServer::GetInstance()->Add(new ModeGame(), 0, "gamemain");
	}
}