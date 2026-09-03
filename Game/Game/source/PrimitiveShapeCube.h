#pragma once
#include "PrimitiveShapeBase.h"
#include "Vector/Vector3.h"

/// @brief 立方体の形状を表すクラス
class PrimitiveShapeCube : public PrimitiveShapeBase
{
public:

	PrimitiveShapeCube() = default;
	~PrimitiveShapeCube() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 描画関数
	void Render() override;

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 立方体を作成する関数
	///
	/// @param origin 立方体の原点座標
	/// @param size 立方体のサイズ
	void CreateCube(const Vec3::Vector3& origin, const Vec3::Vector3& size = Vec3::Vector3(100.0f, 100.0f, 100.0f));

	/// @brief 立方体を追加する関数
	///
	/// @param origin 立方体の原点座標
	/// @param size 立方体のサイズ
	void AddCube(const Vec3::Vector3& origin, const Vec3::Vector3& size = Vec3::Vector3(100.0f, 100.0f, 100.0f));

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 立方体の頂点を作成する関数
	///
	/// @param origin 立方体の原点座標
	/// @param size 立方体のサイズ
	void CreateCubeVertices(const Vec3::Vector3& origin, const Vec3::Vector3& size);

};

