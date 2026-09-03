#include "PrimitiveShapePlane.h"
#include <array>
#include <limits>
#include <cstddef>

namespace
{
	constexpr int VERTICES_PER_PLANE = 4;	// 平面の頂点数
	constexpr int INDICES_PER_PLANE = 6;	// 平面のインデックス数

	// ディフューズカラーとスペキュラカラーのデフォルト値
	constexpr COLOR_U8 DEFAULT_DIFFUSE = { 255, 255, 255, 255 };
	constexpr COLOR_U8 DEFAULT_SPECULAR = { 0, 0, 0, 0 };

	// 初期の法線ベクトル（上向き）
	const VECTOR DEFAULT_NORMAL = { 0.0f, 1.0f, 0.0f };

	// UV座標
	constexpr std::array<float, VERTICES_PER_PLANE> U_LIST = { 0.0f, 0.0f, 1.0f, 1.0f };
	constexpr std::array<float, VERTICES_PER_PLANE> V_LIST = { 0.0f, 1.0f, 0.0f, 1.0f };
}

void PrimitiveShapePlane::Render()
{
	// 基底クラスの描画
	PrimitiveShapeBase::Render();
}

void PrimitiveShapePlane::CreatePlane(const Vec3::Vector3& origin, float size)
{
	// 既存のプリミティブデータをクリア
	ClearPrimitiveData();

	// 平面の頂点を作成
	AddPlane(origin, size);
}

void PrimitiveShapePlane::AddPlane(const Vec3::Vector3& origin, float size)
{
	// 平面の頂点を作成
	CreatePlaneVertices(origin, size);
}

void PrimitiveShapePlane::CreatePlaneVertices(const Vec3::Vector3& origin, float size)
{
	// インデックスの最大値を取得
	constexpr std::size_t maxIndex = (std::numeric_limits<unsigned short>::max)();

	// 必要な頂点数を計算
	constexpr std::size_t maxVertexCount = maxIndex + 1;

	// 追加する平面の頂点数が範囲内か確認
	if(m_vertices.size() + VERTICES_PER_PLANE > maxVertexCount) { return; }

	// 平面のローカル座標を計算
	float halfSize = size * 0.5f;
	const std::array<Vec3::Vector3, VERTICES_PER_PLANE>localPositions = 
	{
		Vec3::Vector3(-halfSize, 0.0f, -halfSize),
		Vec3::Vector3(-halfSize, 0.0f, halfSize),
		Vec3::Vector3(halfSize, 0.0f, -halfSize),
		Vec3::Vector3(halfSize, 0.0f, halfSize)
	};

	// この平面が追加される頂点番号
	const unsigned short vertexOffset = static_cast<unsigned short>(m_vertices.size());

	// 頂点を作成
	for(int i = 0; i < VERTICES_PER_PLANE; ++i)
	{
		// ローカル座標に原点座標を加えてワールド座標にする
		const Vec3::Vector3 position = localPositions[i] + origin;

		VERTEX3D vertex{};

		// Vector3からDxLibのVECTORへ変換
		vertex.pos = VGet(
			position.GetX(),
			position.GetY(),
			position.GetZ()
		);

		vertex.norm		= DEFAULT_NORMAL;
		vertex.dif		= DEFAULT_DIFFUSE;
		vertex.spc		= DEFAULT_SPECULAR;
		vertex.u		= U_LIST[i];
		vertex.v		= V_LIST[i];

		m_vertices.emplace_back(vertex);
	}

	// 1枚目の三角形
	m_indices.emplace_back(vertexOffset + 0);
	m_indices.emplace_back(vertexOffset + 1);
	m_indices.emplace_back(vertexOffset + 2);

	// 2枚目の三角形
	m_indices.emplace_back(vertexOffset + 2);
	m_indices.emplace_back(vertexOffset + 1);
	m_indices.emplace_back(vertexOffset + 3);
}