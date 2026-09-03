#pragma once
#include "PrimitiveShapeBase.h"
#include "Vector/Vector3.h"

/// @brief 平面の形状を表すクラス
class PrimitiveShapePlane : public PrimitiveShapeBase
{
public:

	PrimitiveShapePlane() = default;
	~PrimitiveShapePlane() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 描画関数
	void Render() override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 平面を作成する関数
	///
	/// @param origin 平面の原点座標
	/// @param size 平面のサイズ
	void CreatePlane(const Vec3::Vector3& origin, float size = 100.0f);

	/// @brief 平面を追加する関数
	///
	/// @param origin 平面の原点座標
	/// @param size 平面のサイズ
	void AddPlane(const Vec3::Vector3& origin, float size = 100.0f);

	/// @brief グリッド平面を作成する関数
	///
	/// @param origin 平面の原点座標
	/// @param tileSize タイルのサイズ
	/// @param tileX タイルのX方向の数
	/// @param tileZ タイルのZ方向の数
	void CreateGridPlane(const Vec3::Vector3& origin, float tileSize, int tileX, int tileZ);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 平面の頂点を作成する関数
	///
	/// @param origin 平面の原点座標
	/// @param size 平面のサイズ
	void CreatePlaneVertices(const Vec3::Vector3& origin, float size = 100.0f);
};

