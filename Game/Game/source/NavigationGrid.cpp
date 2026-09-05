#include "NavigationGrid.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace
{
	// キャラクターの半径
	constexpr float CHARACTER_RADIUS = 30.0f;

	// 壁との距離に余裕を持たせる
	constexpr float PATH_MARGIN = 10.0f;

	// 4方向移動
	constexpr int DIRECTIONS[4][2] =
	{
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
	};
}

void NavigationGrid::Build(const std::vector<Math::AABB>& wallColliders)
{
	// ナビゲーショングリッドのノードを初期化
	m_nodes.clear();
	m_nodes.resize(GRID_WIDTH * GRID_HEIGHT);

	// 経路探索用のノードを初期化
	for(int z = 0; z < GRID_HEIGHT; ++z)
	{
		for(int x = 0; x < GRID_WIDTH; ++x)
		{
			NavNodeData& node = m_nodes[z * GRID_WIDTH + x];

			// ノードの座標を設定
			node.x			= x;
			node.z			= z;
			node.isWalkable = true;
			node.gCost		= 0.0f;
			node.hCost		= 0.0f;
			node.parent		= nullptr;

			for(auto& wall : wallColliders)
			{
				// 壁と重なっている場合は歩行不可にする
				if(IsCellOverlappingWall(x, z, wall))
				{
					node.isWalkable = false;
					break;
				}
			}
		}
	}
}

std::vector<Vec3::Vector3> NavigationGrid::FindPath(
	const Vec3::Vector3& startWorldPos,
	const Vec3::Vector3& goalWorldPos)
{
	std::vector<Vec3::Vector3> result;

	// ワールド座標をノードに変換
	NavNodeData* startNode = WorldToNode(startWorldPos);
	NavNodeData* goalNode = WorldToNode(goalWorldPos);
	if(!startNode || !goalNode) { return result; }

	// スタート地点またはゴール地点が壁の中の場合
	if(!startNode->isWalkable || !goalNode->isWalkable) { return result; }

	// 経路探索用のノードをリセット
	ResetSearchData();

	// オープンリストとクローズドリストを用意
	std::vector<NavNodeData*> openList;
	std::vector<NavNodeData*> closedList;

	// スタートノードの初期化
	startNode->gCost = 0.0f;
	startNode->hCost = CalculateHeuristic(*startNode, *goalNode);
	startNode->parent = nullptr;

	// スタートノードをオープンリストに追加
	openList.push_back(startNode);

	// A*アルゴリズムのメインループ
	while(!openList.empty())
	{
		// Fコストが最小のノードを取得
		auto currentIt =
			std::min_element(openList.begin(), openList.end(), [](const NavNodeData* a, const NavNodeData* b)
		{
			// Fコストが同じ場合はHコストで比較
			if(a->GetFCost() == b->GetFCost())
			{
				return a->hCost < b->hCost;
			}

			// Fコストが小さい方を優先
			return a->GetFCost() < b->GetFCost();
		});

		// 現在のノードをオープンリストから削除し、クローズドリストに追加
		NavNodeData* current = *currentIt;
		openList.erase(currentIt);
		closedList.push_back(current);

		// ゴールに到達
		if(current == goalNode)
		{
			NavNodeData* pathNode = goalNode;

			// ゴールからスタートまでの経路を逆順で取得
			while(pathNode)
			{
				// ノードをワールド座標に変換して結果に追加
				result.push_back(NodeToWorld(*pathNode));
				pathNode = pathNode->parent;
			}

			// ゴールからスタートの順番になっているため反転
			std::reverse(result.begin(), result.end());

			// スタート地点は不要
			if(!result.empty()) { result.erase(result.begin()); }

			return result;
		}

		// 隣接ノードを調べる
		for(auto& direction : DIRECTIONS)
		{
			// 隣接ノードの座標を計算
			int nextX = current->x + direction[0];
			int nextZ = current->z + direction[1];

			// 隣接ノードを取得
			NavNodeData* neighbor = GetNode(nextX, nextZ);

			if(!neighbor || !neighbor->isWalkable) { continue; }

			// クローズドリストに存在する場合はスキップ
			if(std::find(
				closedList.begin(), closedList.end(), neighbor) != closedList.end())
			{
				continue;
			}

			// 新しいコストを計算
			float newCost = current->gCost + CELL_SIZE;

			// 隣接ノードがオープンリストに存在するかどうかを判定
			bool isNewNode =
				std::find(openList.begin(), openList.end(), neighbor) == openList.end();

			// 新しいノード、または新しいコストが小さい場合は更新
			if(isNewNode || newCost < neighbor->gCost)
			{
				// 隣接ノードのコストと親ノードを更新
				neighbor->gCost = newCost;
				neighbor->hCost = CalculateHeuristic(*neighbor, *goalNode);
				neighbor->parent = current;

				// オープンリストに存在しない場合は追加
				if(isNewNode) { openList.push_back(neighbor); }
			}
		}
	}

	// 経路が見つからなかった
	return result;
}

NavNodeData* NavigationGrid::WorldToNode(const Vec3::Vector3& worldPos)
{
	// ワールド座標をナビゲーショングリッドのノード座標に変換
	int x = static_cast<int>((worldPos.GetX() - MIN_X) / CELL_SIZE);
	int z = static_cast<int>((worldPos.GetZ() - MIN_Z) / CELL_SIZE);

	// マップ外に出た場合は端に収める
	x = std::clamp(x, 0, GRID_WIDTH - 1);
	z = std::clamp(z, 0, GRID_HEIGHT - 1);

	return GetNode(x, z);
}

Vec3::Vector3 NavigationGrid::NodeToWorld(const NavNodeData& node) const
{
	// ノード座標をワールド座標に変換
	float x = MIN_X + (static_cast<float>(node.x) + 0.5f) * CELL_SIZE;
	float z = MIN_Z + (static_cast<float>(node.z) + 0.5f) * CELL_SIZE;

	// Y座標は0.0fに固定
	return Vec3::Vector3(x, 0.0f, z);
}

bool NavigationGrid::IsInside(int x, int z) const
{
	return 
		x >= 0 && x < GRID_WIDTH &&
		z >= 0 && z < GRID_HEIGHT;
}

NavNodeData* NavigationGrid::GetNode(int x, int z)
{
	// 指定された座標がナビゲーショングリッドの範囲内にない場合はnullptrを返す
	if(!IsInside(x, z)) { return nullptr; }

	// ノードのインデックスを計算して返す
	return &m_nodes[z * GRID_WIDTH + x];
}

const NavNodeData* NavigationGrid::GetNode(int x, int z) const
{
	// 指定された座標がナビゲーショングリッドの範囲内にない場合はnullptrを返す
	if(!IsInside(x, z)) { return nullptr; }

	// ノードのインデックスを計算して返す
	return &m_nodes[z * GRID_WIDTH + x];
}

void NavigationGrid::ResetSearchData()
{
	// 経路探索用のノードをリセット
	for(auto& node : m_nodes)
	{
		node.gCost = 0.0f;
		node.hCost = 0.0f;
		node.parent = nullptr;
	}
}

bool NavigationGrid::IsCellOverlappingWall(int x, int z, const Math::AABB& wall) const
{
	// キャラクターの半径と壁との距離に余裕を持たせる
	float inflate = CHARACTER_RADIUS + PATH_MARGIN;

	// 壁の範囲を拡張
	float wallMinX = wall.min.GetX() - inflate;
	float wallMaxX = wall.max.GetX() + inflate;
	float wallMinZ = wall.min.GetZ() - inflate;
	float wallMaxZ = wall.max.GetZ() + inflate;

	// セルの範囲を計算
	float cellMinX = MIN_X + static_cast<float>(x) * CELL_SIZE;
	float cellMaxX = cellMinX + CELL_SIZE;
	float cellMinZ = MIN_Z + static_cast<float>(z) * CELL_SIZE;
	float cellMaxZ = cellMinZ + CELL_SIZE;

	// セルと壁が重なっているかどうかを判定
	return
		cellMinX <= wallMaxX &&
		cellMaxX >= wallMinX &&
		cellMinZ <= wallMaxZ &&
		cellMaxZ >= wallMinZ;
}

float NavigationGrid::CalculateHeuristic(const NavNodeData& from, const NavNodeData& to) const
{
	// ノード間の距離を計算
	float distanceX = static_cast<float>(std::abs(from.x - to.x));
	float distanceZ = static_cast<float>(std::abs(from.z - to.z));

	// 4方向移動なのでマンハッタン距離
	return (distanceX + distanceZ) * CELL_SIZE;
}