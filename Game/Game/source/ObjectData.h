#pragma once
#include "Vector/Vector3.h"

/// @brief オブジェクトデータ構造体
struct ObjectData
{
	Vec3::Vector3 pos;	/// オブジェクトの位置
	Vec3::Vector3 rot;	/// オブジェクトの回転
	int handle;			/// オブジェクトのグラフィックハンドル

	ObjectData()
	{
		pos		= { 0.0f, 0.0f, 0.0f };
		rot		= { 0.0f, 0.0f, 0.0f };
		handle	= -1;
	}
};
