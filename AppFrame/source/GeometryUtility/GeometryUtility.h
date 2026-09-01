#pragma once
#include "../Vector/Vector3.h"
#include <cmath>

/// @brief 幾何計算用の便利関数クラス
namespace GeometryUtility
{
	//===========================================================================
	// 判定
	//===========================================================================

	/// @brief 対象が前方にあるかどうかを判定する関数
	///
	/// @param fromPos 判定元の位置
	/// @param fromDir 判定元の方向ベクトル
	/// @param targetPos 判定対象の位置
	/// @param dotThreshold 前方判定の内積閾値(デフォルトは0.0f)
	/// 
	/// @return 対象が前方にある場合はtrue、そうでない場合はfalse
	bool IsFacing(const Vec3::Vector3& fromPos, const Vec3::Vector3& fromDir, const Vec3::Vector3& targetPos, float dotThreshold = 0.0f);

	//========================================================================
	// 変換
	//========================================================================

	/// @brief ローカル座標をワールド座標に変換する関数
	///
	/// @param localDir ローカル方向ベクトル
	/// @param forward 前方向ベクトル
	/// 
	/// @return ワールド座標
	Vec3::Vector3 ConvertLocalToWorld(const Vec3::Vector3& localDir, const Vec3::Vector3& forwardDir);

	//========================================================================
	// 方向ベクトル取得
	//========================================================================

	/// @brief 前方向ベクトルを取得する関数
	///
	/// @param yaw Yaw角度（ラジアン）
	/// 
	/// @return 前方向ベクトル
	inline Vec3::Vector3 GetForwardVec(float yaw) { return Vec3::Vector3(sinf(yaw), 0.0f, cosf(yaw)); }
	
	/// @brief 右方向ベクトルを取得する関数
	///
	/// @param yaw Yaw角度（ラジアン）
	/// 
	/// @return 右方向ベクトル
	inline Vec3::Vector3 GetRightVec(float yaw) { return Vec3::Vector3(cosf(yaw), 0.0f, -sinf(yaw)); }

}