#include "GameCamera.h"

namespace
{
	/// @brief 初期カメラ設定
	namespace Default
	{
		const VECTOR CAMERA_POS = VGet(73.636536f, 86.688026f, -140.440582f);
		const VECTOR CAMERA_TARGET = VGet(-12.230986f, 59.101776f, -15.002045f);

		//const VECTOR CAMERA_POS = { 0.0f, 10.0f, 0.0f };	/// @brief カメラの初期位置
		//const VECTOR CAMERA_TARGET = { 0.0f, 0.0f, 0.0f };	/// @brief カメラの初期注視点
		const VECTOR CAMERA_UPVEC = { 0.0f, 1.0f, 0.0f };	/// @brief カメラの初期アップベクトル
	}
}

GameCamera::GameCamera()
{
	m_cameraData.pos	= Default::CAMERA_POS;
	m_cameraData.target = Default::CAMERA_TARGET;
	m_cameraData.upVec	= Default::CAMERA_UPVEC;
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Initialize()
{
	return true;
}

bool GameCamera::Terminate()
{
	return true;
}

bool GameCamera::Process()
{
	auto offset = VGet(0.0f, 10.0f, -20.0f);
	m_cameraData.pos.y += offset.y;

	return true;
}

bool GameCamera::SetUpCamera() const
{
	/*SetCameraPositionAndTarget_UpVecY(VGet(73.636536f, 86.688026f, -140.440582f), VGet(-12.230986f, 59.101776f, -15.002045f));
	SetCameraNearFar(2.376863f, 594.215820f);*/


	// カメラの位置と注視点を設定
	SetCameraPositionAndTarget_UpVecY(m_cameraData.pos, m_cameraData.target);

	// カメラの近クリップ距離と遠クリップ距離を設定
	SetCameraNearFar(m_clipNear, m_clipFar);

	return true;
}