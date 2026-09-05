#include "DebugNavigationGrid.h"
#include "DxLib.h"
#include "DebugManager.h"

namespace
{
	constexpr float GRID_DRAW_HEIGHT = 3.0f;
	const int WALKABLE_COLOR = GetColor(0, 255, 0);
	const int BLOCKED_COLOR = GetColor(255, 0, 0);
}

void DebugNavigationGrid::Render(
	const NavigationGrid& navigationGrid) const
{
	// デバッグコリジョンマネージャーのインスタンスを取得
	auto& debugCol = DebugManager::GetInstance().GetDebugCollision();
	if(!&debugCol) { return; }

	debugCol.AddColItem([&navigationGrid, this]()
		{
			const auto& nodes = navigationGrid.GetNodes();

			// NavigationGrid::Build前の場合
			if(nodes.empty())
			{
				return;
			}

			for(const NavNodeData& node : nodes)
			{
				float minX =
					NavigationGrid::MIN_X +
					static_cast<float>(node.x) * NavigationGrid::CELL_SIZE;

				float minZ =
					NavigationGrid::MIN_Z +
					static_cast<float>(node.z) * NavigationGrid::CELL_SIZE;

				float maxX = minX + NavigationGrid::CELL_SIZE;
				float maxZ = minZ + NavigationGrid::CELL_SIZE;

				int color =
					node.isWalkable
					? WALKABLE_COLOR
					: BLOCKED_COLOR;

				DrawCell(minX, minZ, maxX, maxZ, color);
			}
		});
}

void DebugNavigationGrid::DrawCell(
	float minX,
	float minZ,
	float maxX,
	float maxZ,
	int color) const
{
	VECTOR leftTop = VGet(minX, GRID_DRAW_HEIGHT, minZ);
	VECTOR rightTop = VGet(maxX, GRID_DRAW_HEIGHT, minZ);
	VECTOR leftBottom = VGet(minX, GRID_DRAW_HEIGHT, maxZ);
	VECTOR rightBottom = VGet(maxX, GRID_DRAW_HEIGHT, maxZ);

	DrawLine3D(leftTop, rightTop, color);
	DrawLine3D(rightTop, rightBottom, color);
	DrawLine3D(rightBottom, leftBottom, color);
	DrawLine3D(leftBottom, leftTop, color);
}