#pragma once

/// @brief ナビゲーションノード構造体
struct NavNode
{
	int x;				// ノードのX座標
	int z;				// ノードのZ座標
	float gCost;		// スタートノードからの移動コスト
	float hCost;		// ゴールノードまでの推定コスト
	bool isWalkable;	// 歩行可能かどうか
	NavNode* parent;	// 親ノードへのポインタ

	NavNode()
	{
		x			= 0;
		z			= 0;
		gCost		= 0.0f;
		hCost		= 0.0f;
		isWalkable	= true;
		parent		= nullptr;
	}

	/// @brief Fコストを取得する関数
	///
	/// @return Fコストの値
	float GetFCost() const { return gCost + hCost; }
};



///// @brief ナビゲーションノード構造体
//struct NavNode
//{
//	int x;				// ノードのX座標
//	int z;				// ノードのZ座標
//	bool isWalkable;	// 歩行可能かどうか
//
//	NavNode()
//	{
//		x			= 0;
//		z			= 0;
//		isWalkable	= true;
//	}
//};
//
///// @brief パスノード構造体
//struct PathNode
//{
//	float gCost;		// スタートノードからの移動コスト
//	float hCost;		// ゴールノードまでの推定コスト
//	NavNode* parent;	// 親ノードへのポインタ
//
//	PathNode()
//	{
//		gCost	= 0.0f;
//		hCost	= 0.0f;
//		parent	= nullptr;
//	}
//
//	/// @brief Fコストを取得する関数
//	///
//	/// @return Fコストの値
//	float GetFCost() const { return gCost + hCost; }
//};