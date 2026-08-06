#pragma once
#include "../../Vector/Vector3.h"

namespace Collision::Shape
{
	/// @brief 球のデータ構造体
	struct Sphere
	{
		Vec3::Vector3 center;	/// 球の中心座標
		float radius;			/// 球の半径

		Sphere()
		{
			center = Vec3::Vector3(0.0f, 0.0f, 0.0f);
			radius = 1.0f;
		}
	};
}