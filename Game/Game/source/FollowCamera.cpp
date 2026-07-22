#include "FollowCamera.h"
#include "ObjectData.h"
#include "VectorConverter/VectorConverter.h"
#include <cmath>

namespace
{
	// 円周率
	constexpr float PI = 3.1415926535f;

	// カメラの回転速度
	constexpr float ROTATE_SPEED = 0.05f;

	// 追従するオブジェクトからカメラへのオフセット
	const Vec3::Vector3 POS_OFFSET = { 0.0f, 300.0f, -150.0f };

	// 追従するオブジェクトへのオフセット
	const Vec3::Vector3 TARGET_OFFSET = { 0.0f, 100.0f, 0.0f };
}

FollowCamera::FollowCamera(const ObjectData& target)
	: m_targetObject(target)
	, m_posOffset(POS_OFFSET)
	, m_targetOffset(TARGET_OFFSET)
{
	m_cameraData.upVec = { 0.0f, 1.0f, 0.0f };
}

void FollowCamera::Update()
{
	// カメラ入力を更新
	m_cameraInput.Update();

	// カメラの回転を更新
	UpdateCameraRotation();

	// カメラの位置を更新
	UpdateCameraPosition();
}

void FollowCamera::SetUpCamera() const
{
	// カメラの位置と注視点を設定
	//SetCameraPositionAndTarget_UpVecY(cameraPos, m_targetObject.pos);

	// カメラの位置と注視点とアップベクトルを設定
	SetCameraPositionAndTargetAndUpVec
	(
		Vec::ToDxVec(m_cameraData.pos),		// カメラの位置
		Vec::ToDxVec(m_cameraData.target),	// カメラの注視点
		Vec::ToDxVec(m_cameraData.upVec)	// カメラのアップベクトル
	);

	// カメラの近クリップ距離と遠クリップ距離を設定
	SetCameraNearFar(m_clipNear, m_clipFar);
}

void FollowCamera::UpdateCameraPosition()
{
	// カメラの注視点をオブジェクトの位置に設定
	m_cameraData.target = m_targetObject.pos + m_targetOffset;

	// カメラの位置を更新
	m_cameraData.pos = m_targetObject.pos + CalcPitchOffset();
}

Vec3::Vector3 FollowCamera::CalcYawOffset() const
{
	// ヨー角のsinとcosを計算
	float sinYaw = std::sin(m_yaw);
	float cosYaw = std::cos(m_yaw);

	// オフセットをヨー角に応じて回転
	float rotatedX = m_posOffset.GetX() * cosYaw - m_posOffset.GetZ() * sinYaw;
	float rotatedZ = m_posOffset.GetX() * sinYaw + m_posOffset.GetZ() * cosYaw;

	// 計算したヨーオフセットを返す
	return { rotatedX, m_posOffset.GetY(), rotatedZ };
}

Vec3::Vector3 FollowCamera::CalcPitchOffset() const
{
	// ヨー角のオフセットを計算
	Vec3::Vector3 yawOffset = CalcYawOffset();

	// カメラの前方向を計算
	Vec3::Vector3 forward = { -yawOffset.GetX(), 0.0f, -yawOffset.GetZ() };
	forward = forward.Normalize();

	// ワールド上方向
	const Vec3::Vector3 worldUp = { 0.0f,1.0f,0.0f };

	// カメラの右方向を計算
	Vec3::Vector3 right = worldUp.Cross(forward).Normalize();

	// ピッチ角のsinとcosを計算
	float sinPitch = std::sin(m_pitch);
	float cosPitch = std::cos(m_pitch);

	/****** ロドリゲスの回転公式 ******/

	// 回転軸を計算
	Vec3::Vector3 cross = right.Cross(yawOffset);

	// 回転軸と回転前のベクトルの内積を計算
	float dot = right.Dot(yawOffset);

	// 回転後のオフセットを計算
	Vec3::Vector3 rotatedOffset =
	{
		// 計算式
		// v_rot = v * cosθ + cross * sinθ + k * dot * (1 - cosθ)

		yawOffset.GetX() * cosPitch + cross.GetX() * sinPitch + right.GetX() * dot * (1.0f - cosPitch),
		yawOffset.GetY() * cosPitch + cross.GetY() * sinPitch + right.GetY() * dot * (1.0f - cosPitch),
		yawOffset.GetZ() * cosPitch + cross.GetZ() * sinPitch + right.GetZ() * dot * (1.0f - cosPitch)
	};

	return rotatedOffset;
}

void FollowCamera::UpdateCameraRotation()
{
	// カメラのヨー角を更新
	m_yaw += m_cameraInput.GetRotateX() * ROTATE_SPEED;

	// カメラのピッチ角を更新
	m_pitch += m_cameraInput.GetRotateY() * ROTATE_SPEED;
}