#include "ModeGame.h"
#include "FollowCamera.h"
#include "Player.h"
#include "InputManager.h"

ModeGame::ModeGame() = default;
ModeGame::~ModeGame() = default;

bool ModeGame::Initialize()
{
	if(!base::Initialize()) { return false; }

	// マネージャークラスの生成
	CreateManagers();

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



	//const Pad& pad = InputManager::GetInstance().GetPad(0);
	//// --- スティック入力のテスト ---
	//if(pad.IsConnected())
	//{
	//	double lx = pad.GetLeftStickX();
	//	double ly = pad.GetLeftStickY();
	//	printfDx("Left Stick: X=%.2f, Y=%.2f\n", lx, ly);

	//	double rx = pad.GetRightStickX();
	//	double ry = pad.GetRightStickY();
	//	printfDx("Right Stick: X=%.2f, Y=%.2f\n", rx, ry);
	//}



	// オブジェクトの更新処理
	m_objectManager->Update();
	
	// カメラマネージャーの更新
	m_cameraManager->Update();

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

	return true;
}

void ModeGame::CreateManagers()
{
	// カメラマネージャーの生成
	m_cameraManager = std::make_unique<CameraManager>();

	// オブジェクトマネージャーの生成
	m_objectManager = std::make_unique<ObjectManager>();
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