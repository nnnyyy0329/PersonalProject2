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
		pos = VGet(73.636536f, 86.688026f, -140.440582f);
		target = VGet(-12.230986f, 59.101776f, -15.002045f);
		/*pos		= { 0.0f, 0.0f, 0.0f };
		target	= { 0.0f, 0.0f, 1.0f };*/
		upVec	= { 0.0f, 1.0f, 0.0f };
	}
};
