#include "PrimitiveShapeBase.h"

void PrimitiveShapeBase::Render()
{
	if(m_textureHandle == -1) { return; }

	if(m_vertices.empty() || m_indices.empty()) { return; }

	int vertexCount = static_cast<int>(m_vertices.size());		// 頂点数
	int polygonCount = static_cast<int>(m_indices.size() / 3);	// ポリゴン数

	// 3Dポリゴンを描画する
	int result = DrawPolygonIndexed3D(
		m_vertices.data(),
		vertexCount,
		m_indices.data(),
		polygonCount,
		m_textureHandle,
		FALSE
	);
}

void  PrimitiveShapeBase::ClearPrimitiveData()
{
	m_vertices.clear();
	m_indices.clear();
}
