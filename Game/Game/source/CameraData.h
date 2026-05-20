#pragma once
#include "DxLib.h"

/// @brief カメラデータ構造体
struct CameraData
{
	VECTOR pos;		///< カメラの位置
	VECTOR target;	///< カメラの注視点
	VECTOR upVec;	///< カメラのアップベクトル

	CameraData()
	{
		pos		= {};
		target	= {};
		upVec	= {};
	}
};
