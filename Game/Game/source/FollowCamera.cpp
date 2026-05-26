#include "FollowCamera.h"
#include "ObjectData.h"

namespace
{
	// 追従するオブジェクトからのオフセット
	const VECTOR OFFSET = VGet(0.0f, 300.0f, -150.0f);	
}

FollowCamera::FollowCamera(const ObjectData& target)
	: m_targetObject(target)
	, m_offset(OFFSET)
{
	m_cameraData.upVec = VGet(0.0f, 1.0f, 0.0f);
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Update()
{
	// カメラの位置を更新
	UpdateCameraPosition();
}

void FollowCamera::UpdateCameraPosition()
{
	// カメラの注視点をオブジェクトの位置に設定
	m_cameraData.target = m_targetObject.pos;

	// オブジェクトの位置にオフセットを加えてカメラの位置を設定
	m_cameraData.pos = VAdd(m_targetObject.pos, m_offset);
}

void FollowCamera::SetUpCamera() const
{
	// カメラの位置と注視点を設定
	//SetCameraPositionAndTarget_UpVecY(cameraPos, m_targetObject.pos);

	// カメラの位置と注視点とアップベクトルを設定
	SetCameraPositionAndTargetAndUpVec
	(
		m_cameraData.pos,		// カメラの位置
		m_targetObject.pos,		// カメラの注視点
		m_cameraData.upVec		// カメラのアップベクトル
	);

	// カメラの近クリップ距離と遠クリップ距離を設定
	SetCameraNearFar(m_clipNear, m_clipFar);
}