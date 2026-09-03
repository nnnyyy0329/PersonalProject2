#include "PrimitiveShapeCube.h"
#include <array>
#include <limits>
#include <cstddef>

namespace
{
	constexpr int CUBE_FACE_COUNT = 6;		// 立方体の面の数
	constexpr int VERTICES_PER_FACE = 4;	// 面ごとの頂点数
	constexpr int INDICES_PER_FACE = 6;		// 面ごとのインデックス数

	// ディフューズカラーとスペキュラカラーのデフォルト値
	constexpr COLOR_U8 DEFAULT_DIFFUSE	= { 255, 255, 255, 255 };
	constexpr COLOR_U8 DEFAULT_SPECULAR = { 0, 0, 0, 0 };

	// 6面分の法線ベクトル
	const std::array<Vec3::Vector3, CUBE_FACE_COUNT> NORMAL_LIST =
	{
		Vec3::Vector3(0.0f, 0.0f, -1.0f), 	// 前面
		Vec3::Vector3(1.0f, 0.0f, 0.0f),	// 右側面
		Vec3::Vector3(0.0f, 0.0f, 1.0f),	// 背面
		Vec3::Vector3(-1.0f, 0.0f, 0.0f),	// 左側面
		Vec3::Vector3(0.0f, 1.0f, 0.0f),	// 上面
		Vec3::Vector3(0.0f, -1.0f, 0.0f)	// 底面
	};

	// UV座標
	constexpr std::array<float, VERTICES_PER_FACE> U_LIST = { 0.0f, 0.0f, 1.0f, 1.0f };
	constexpr std::array<float, VERTICES_PER_FACE> V_LIST = { 0.0f, 1.0f, 0.0f, 1.0f };
}

void PrimitiveShapeCube::Render()
{
	// 基底クラスの描画
	PrimitiveShapeBase::Render();
}

void PrimitiveShapeCube::CreateCube(const Vec3::Vector3& origin, const Vec3::Vector3& size)
{
	// 既存のプリミティブデータをクリア
	ClearPrimitiveData();

	// 立方体の頂点を作成
	CreateCubeVertices(origin, size);
}

void PrimitiveShapeCube::AddCube(const Vec3::Vector3& origin, const Vec3::Vector3& size)
{
	// 立方体の頂点を作成
	CreateCubeVertices(origin, size);
}

void PrimitiveShapeCube::CreateCubeVertices(const Vec3::Vector3& origin, const Vec3::Vector3& size)
{
	// インデックスの最大値を取得
	constexpr std::size_t maxIndex = (std::numeric_limits<unsigned short>::max)();

	// 立方体の面の数と面ごとの頂点数から必要な頂点数を計算
	const std::size_t requiredVertexCount = CUBE_FACE_COUNT * VERTICES_PER_FACE;

	// インデックスの最大値から頂点の最大数を計算
	const std::size_t maxVertexCount = maxIndex + 1;

	// 既存の頂点数と必要な頂点数を比較して、最大頂点数を超える場合は処理を中断
	if(m_vertices.size() + requiredVertexCount > maxVertexCount) { return; }

	// 立方体のサイズの半分を計算
	const Vec3::Vector3 halfSize = size * 0.5f;

	// キューブの基本8頂点
	const Vec3::Vector3 position0(-halfSize.GetX(), halfSize.GetY(), -halfSize.GetZ());
	const Vec3::Vector3 position1(-halfSize.GetX(), halfSize.GetY(), halfSize.GetZ());
	const Vec3::Vector3 position2(halfSize.GetX(), halfSize.GetY(), -halfSize.GetZ());
	const Vec3::Vector3 position3(halfSize.GetX(), halfSize.GetY(), halfSize.GetZ());
	const Vec3::Vector3 position4(-halfSize.GetX(), -halfSize.GetY(), -halfSize.GetZ());
	const Vec3::Vector3 position5(-halfSize.GetX(), -halfSize.GetY(), halfSize.GetZ());
	const Vec3::Vector3 position6(halfSize.GetX(), -halfSize.GetY(), -halfSize.GetZ());
	const Vec3::Vector3 position7(halfSize.GetX(), -halfSize.GetY(), halfSize.GetZ());

	// 各面の頂点（6面分）
	const std::array<std::array<Vec3::Vector3, VERTICES_PER_FACE>, CUBE_FACE_COUNT> faceList =
	{
		{
		// Front
			{
				position4,
				position0,
				position6,
				position2
			},

		// Right
			{
				position6,
				position2,
				position7,
				position3
			},

		// Back
			{
				position7,
				position3,
				position5,
				position1
			},

		// Left
			{
				position5,
				position1,
				position4,
				position0
			},

		// Top
			{
				position0,
				position1,
				position2,
				position3
			},

		// Bottom
			{
				position4,
				position5,
				position6,
				position7
			}
		}
	};

	// 既存の頂点数をオフセットの開始位置にする
	const unsigned short vertexOffset = static_cast<unsigned short>(m_vertices.size());

	// 各面の頂点を作成
	for(int face = 0; face < CUBE_FACE_COUNT; ++face)
	{
		// 各面の頂点を作成
		for(int vertexIndex = 0; vertexIndex < VERTICES_PER_FACE; ++vertexIndex)
		{
			// 面の頂点座標に原点を加算してワールド座標に変換
			const Vec3::Vector3 position = faceList[face][vertexIndex] + origin;

			VERTEX3D vertex{};

			// Vector3からDxLibのVECTORへ変換

			// 頂点座標を設定
			vertex.pos = VGet(
				position.GetX(),
				position.GetY(),
				position.GetZ()
			);

			// 法線ベクトルを設定
			vertex.norm = VGet(
				NORMAL_LIST[face].GetX(),
				NORMAL_LIST[face].GetY(),
				NORMAL_LIST[face].GetZ()
			);

			vertex.dif	= DEFAULT_DIFFUSE;		// ディフューズカラーを設定
			vertex.spc	= DEFAULT_SPECULAR;		// スペキュラカラーを設定
			vertex.u	= U_LIST[vertexIndex];	// UV座標を設定
			vertex.v	= V_LIST[vertexIndex];	// UV座標を設定
			
			// 頂点をリストに追加
			m_vertices.emplace_back(vertex);
		}

		// 2枚の三角形を形成するためのインデックスを作成
		const unsigned short faceOffset = 
			static_cast<unsigned short>(vertexOffset + face * VERTICES_PER_FACE);

		// 1枚目の三角形
		m_indices.emplace_back(faceOffset + 0);
		m_indices.emplace_back(faceOffset + 1);
		m_indices.emplace_back(faceOffset + 2);

		// 2枚目の三角形
		m_indices.emplace_back(faceOffset + 2);
		m_indices.emplace_back(faceOffset + 1);
		m_indices.emplace_back(faceOffset + 3);
	}
}