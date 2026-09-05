#pragma once
#include "NavNodeData.h"
#include "math/Math.h"
#include "MapData.h"
#include <vector>

/// @brief ナビゲーショングリッドクラス
class NavigationGrid
{
public:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ナビゲーショングリッドの構築関数
	///
	/// @param wallColliders 壁の当たり判定用のAABBリスト
	void Build(const std::vector<Math::AABB>& wallColliders);

	/// @brief ワールド座標から経路を検索する関数
	///
	/// @param startWorldPos 経路探索の開始位置（ワールド座標）
	/// @param goalWorldPos 経路探索の目標位置（ワールド座標）
	/// 
	/// @return 経路探索の結果として得られたワールド座標のリスト
	std::vector<Vec3::Vector3> FindPath(
		const Vec3::Vector3& startWorldPos,
		const Vec3::Vector3& goalWorldPos);

	/// @brief ワールド座標からノードを取得する関数
	///
	/// @param worldPos ワールド座標
	/// 
	/// @return ノードのポインタ。存在しない場合はnullptr
	NavNodeData* WorldToNode(const Vec3::Vector3& worldPos);

	/// @brief ノードからワールド座標を取得する関数
	///
	/// @param node ノード
	/// 
	/// @return ワールド座標
	Vec3::Vector3 NodeToWorld(const NavNodeData& node) const;

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief グリッドの幅を取得する関数
	const std::vector<NavNodeData>& GetNodes() const { return m_nodes; }
	
	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// ナビゲーショングリッドの範囲の定数
	static constexpr float MIN_X		= MapData::GRID_MIN_X;
	static constexpr float MAX_X		= MapData::GRID_MAX_X;
	static constexpr float MIN_Z		= MapData::GRID_MIN_Z;
	static constexpr float MAX_Z		= MapData::GRID_MAX_Z;

	/// ナビゲーショングリッドのセルサイズの定数
	static constexpr float CELL_SIZE	=  50.0f;

	/// ナビゲーショングリッドの幅と高さを計算する定数
	static constexpr int GRID_WIDTH = static_cast<int>((MAX_X - MIN_X) / CELL_SIZE);
	static constexpr int GRID_HEIGHT = static_cast<int>((MAX_Z - MIN_Z) / CELL_SIZE);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 指定された座標がナビゲーショングリッドの範囲内にあるかどうかを判定する関数
	///
	/// @param x 判定するX座標
	/// @param z 判定するZ座標
	/// 
	/// @return 範囲内にある場合はtrue、範囲外の場合はfalse
	bool IsInside(int x, int z) const;

	/// @brief ノードの取得関数
	///
	/// @param x ノードのX座標
	/// @param z ノードのZ座標
	/// 
	/// @return ノードのポインタ。存在しない場合はnullptr
	NavNodeData* GetNode(int x, int z);

	/// @brief ノードの取得関数（const版）
	///
	/// @param x ノードのX座標
	/// @param z ノードのZ座標
	/// 
	/// @return ノードのポインタ。存在しない場合はnullptr
	const NavNodeData* GetNode(int x, int z) const;

	/// @brief 経路探索のデータをリセットする関数
	void ResetSearchData();

	/// @brief 指定されたセルが壁と重なっているかどうかを判定する関数
	///
	/// @param x 判定するセルのX座標
	/// @param z 判定するセルのZ座標
	/// @param wall 壁のAABB
	/// 
	/// @return 重なっている場合はtrue、重なっていない場合はfalse
	bool IsCellOverlappingWall(int x, int z, const Math::AABB& wall) const;

	/// @brief ヒューリスティックコストを計算する関数
	///
	/// @param from 開始ノード
	/// @param to 目標ノード
	/// 
	/// @return ヒューリスティックコストの値
	float CalculateHeuristic(const NavNodeData& from, const NavNodeData& to) const;

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// ナビゲーショングリッドのノード配列
	std::vector<NavNodeData> m_nodes;
};

