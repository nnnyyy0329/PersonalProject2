#include "FollowCamera.h"
#include "ObjectData.h"

FollowCamera::FollowCamera(const ObjectData& target)
	: m_targetObject(target)				// 追従対象のオブジェクトデータへの参照を設定
	, m_offset(VGet(0.0f, 10.0f, -20.0f))	// オブジェクトからのオフセットを設定
{
	
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
{
	
}

void FollowCamera::SetUpCamera() const
{
	// オブジェクトの位置にオフセットを加えて設定
	VECTOR cameraPos = VAdd(m_targetObject.pos, m_offset);

	// カメラの位置と注視点を設定
	SetCameraPositionAndTarget_UpVecY(cameraPos, m_targetObject.pos);

	// カメラの近クリップ距離と遠クリップ距離を設定
	SetCameraNearFar(m_clipNear, m_clipFar);
}