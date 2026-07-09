#pragma once
#include "DxLib.h"
#include "../Vector/Vector3.h"

/// @brief DxLibとVector::Vector3の変換関数群
namespace Vec
{
	/// @brief Vector::Vector3をDxLibのVECTORに変換する関数
	///
	/// @param v 変換するVector::Vector3
	/// 
	/// @return 変換後のDxLibのVECTOR
	inline VECTOR ToDxVec(const Vec3::Vector3& v)
	{
		return VECTOR(v.GetX(), v.GetY(), v.GetZ());
	}

	/// @brief DxLibのVECTORをVector::Vector3に変換する関数
	///
	/// @param v 変換するDxLibのVECTOR
	/// 
	/// @return 変換後のVector::Vector3
	inline Vec3::Vector3 ToVec3(const VECTOR& v)
	{
		return Vec3::Vector3(v.x, v.y, v.z);
	}
}