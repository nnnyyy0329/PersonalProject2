#pragma once
#include "MoveComponent.h"
#include "Vector/Vector3.h"
#include <vector>

class Character;		/// キャラクタークラス
class NavigationGrid;	/// ナビゲーショングリッドクラス

/// @brief 敵の移動コンポーネントクラス
class EnemyMoveComponent : public MoveComponent<Character>
{
public:

	~EnemyMoveComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 更新関数
	///
	/// @param owner 更新処理を行うキャラクター
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	void Update(Character& owner, const GameContext& gameContext) override;

	//===========================================================================
	// ナビゲーション関連関数
	//===========================================================================

	/// @brief A*経路を更新する
	/// 
	/// @param startPos 開始位置
	/// @param targetPos 目標位置
	/// 
	/// @return 経路が更新されたならtrue、経路が更新されなかったならfalseを返す
	bool UpdatePath(const Vec3::Vector3& startPos, const Vec3::Vector3& targetPos);

	/// @brief 経路を削除する
	void ClearPath();

	/// @brief 経路が存在するかどうかを取得する
	///
	///	@return 経路が存在するならtrue、存在しないならfalse
	bool HasPath() const;

	/// @brief 現在向かうべき地点を取得する
	///
	/// @return 現在向かうべき地点の座標
	Vec3::Vector3 GetNextPathPoint() const;

	/// @brief ナビゲーション情報を設定する
	///
	/// @param navigationGrid ナビゲーション情報
	void SetNavigationGrid(NavigationGrid* navigationGrid) { m_navigationGrid = navigationGrid; }

	//===========================================================================
	// 移動関連関数
	//===========================================================================

	/// @brief 指定したオブジェクトの位置に移動する関数
	///
	/// @param targetPos 移動先の位置
	void MoveToTarget(const Vec3::Vector3& targetPos);

	/// @brief 移動ベクトルを取得する関数
	///
	/// @return 移動ベクトル
	Vec3::Vector3 GetMoveVector() const override { return m_moveVector; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================
	
	/// @brief A*経路探索を行う関数
	void AdvancePathPoint();

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// ナビゲーション情報
	NavigationGrid* m_navigationGrid = nullptr;

	/// 移動ベクトル
	std::vector<Vec3::Vector3> m_path;

	/// 現在の経路上のインデックス
	std::size_t m_pathIndex = 0;

	/// 最後に更新したターゲットの位置
	Vec3::Vector3 m_lastTargetPos = Vec3::Vector3(0.0f, 0.0f, 0.0f);

	/// 経路再計算までの待機フレーム数
	int m_repathWaitFrame = 0;
};

