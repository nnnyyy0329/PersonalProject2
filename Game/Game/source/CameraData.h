#pragma once
#include "Vector/Vector3.h"

/// @brief カメラデータ構造体
struct CameraData
{
	/// カメラの位置
	Vec3::Vector3 pos;

	/// カメラの注視点
	Vec3::Vector3 target;

	/// カメラのアップベクトル
	Vec3::Vector3 upVec;

	CameraData()
	{
		pos		= {};
		target	= {};
		upVec	= {};
	}
};
