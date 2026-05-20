#include "CameraManager.h"
#include "CameraBase.h"

CameraManager::CameraManager()
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::Update()
{
	if(!m_currentCamera) { return; }

	// 現在のカメラの更新処理を呼び出す
	m_currentCamera->Update();
}

void CameraManager::SetUpCamera() const
{
	if(!m_currentCamera) { return; }

	// 現在のカメラの設定を適用する
	m_currentCamera->SetUpCamera();
}

void CameraManager::ChangeCamera(std::unique_ptr<CameraBase> newCamera)
{
	// 新しいカメラを現在のカメラに切り替える
	m_currentCamera = std::move(newCamera);
}