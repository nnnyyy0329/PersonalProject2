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