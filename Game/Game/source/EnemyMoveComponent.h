#pragma once
#include "MoveComponent.h"
#include "Vector/Vector3.h"
#include <vector>

class Character;		/// キャラクタークラス
class NavigationGrid;	/// ナビゲーショングリッドクラス

class EnemyMoveComponent : public MoveComponent<Character>
{
public:

	~EnemyMoveComponent() = default;

	//===========================================================================
	// 内部関数
	//===========================================================================

	// ナビゲーション情報を設定する
	void SetNavigationGrid(NavigationGrid* navigationGrid) { m_navigationGrid = navigationGrid; }

	// プレイヤーへの経路を更新する
	bool UpdatePath(const Vec3::Vector3& startPos, const Vec3::Vector3& targetPos);

	// 経路を削除する
	void ClearPath();

	// 経路が存在するか
	bool HasPath() const;

	// 現在向かうべき地点を取得する
	Vec3::Vector3 GetNextPathPoint() const;

	/// @brief 指定したオブジェクトの位置に移動する関数
	///
	/// @param targetPos 移動先の位置
	void MoveToTarget(const Vec3::Vector3& targetPos);

	/// @brief 移動ベクトルを取得する関数
	///
	/// @return 移動ベクトル
	Vec3::Vector3 GetMoveVector() const override { return m_moveVector; }

private:

	void AdvancePathPoint();

	NavigationGrid* m_navigationGrid = nullptr;

	std::vector<Vec3::Vector3> m_path;
	std::size_t m_pathIndex = 0;

	Vec3::Vector3 m_lastTargetPos =
		Vec3::Vector3(0.0f, 0.0f, 0.0f);

	int m_repathWaitFrame = 0;
};

