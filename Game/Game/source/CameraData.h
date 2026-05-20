#pragma once
#include "DxLib.h"

/// @brief カメラデータ構造体
struct CameraData
{
	/// カメラの位置
	VECTOR pos;

	/// カメラの注視点
	VECTOR target;

	/// カメラのアップベクトル
	VECTOR upVec;

	CameraData()
	{
		pos		= {};
		target	= {};
		upVec	= {};
	}
};
