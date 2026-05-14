#include "GameCamera.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Initialize()
{
	m_clipNear	= 2.0f;
	m_clipFar	= 10000.0f;

	return true;
}

bool GameCamera::Terminate()
{
	return true;
}

bool GameCamera::Process()
{
	return true;
}

bool GameCamera::SetUpCamera() const
{
	// カメラの位置と注視点を設定
	SetCameraPositionAndTarget_UpVecY(m_cameraData.pos, m_cameraData.target);

	// カメラの近クリップ距離と遠クリップ距離を設定
	SetCameraNearFar(m_clipNear, m_clipFar);

	return true;
}