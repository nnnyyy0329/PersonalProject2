#include "CameraBase.h"

Vec3::Vector3 CameraBase::GetHorizontalForward() const
{
	// カメラの注視点と位置から前方向ベクトルを計算
	Vec3::Vector3 forward = m_cameraData.target - m_cameraData.pos;

	// Y成分を0
	forward.SetY(0.0f);
	
	// ベクトルを正規化して返す
	return forward.Normalize();
}

Vec3::Vector3 CameraBase::GetHorizontalRight() const
{
	// カメラの前方向ベクトルを取得
	Vec3::Vector3 forward = GetHorizontalForward();

	// 上方向ベクトルを取得
	Vec3::Vector3 worldUp = { 0.0f, 1.0f, 0.0f };

	// 前方向ベクトルと上方向ベクトルの外積を計算して右方向ベクトルを求める
	Vec3::Vector3 right = worldUp.Cross(forward);
	right.SetY(0.0f);

	// ベクトルを正規化して返す
	return right.Normalize();
}