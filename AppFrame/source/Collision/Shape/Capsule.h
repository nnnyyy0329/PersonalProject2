#pragma once
#include "../../Vector/Vector3.h"

namespace Collision::Shape
{
	/// @brief カプセルのデータ構造体
	struct Capsule
	{
		Vec3::Vector3 start;	/// カプセルの上端の座標
		Vec3::Vector3 end;		/// カプセルの下端の座標
		float radius;			/// カプセルの半径

		Capsule()
		{
			start	= Vec3::Vector3(0.0f, 1.0f, 0.0f);
			end		= Vec3::Vector3(0.0f, -1.0f, 0.0f);
			radius	= 1.0f;
		}
	};
}