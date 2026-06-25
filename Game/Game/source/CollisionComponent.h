#pragma once
#include "IComponent.h"
#include "CollisionData.h"

/// @brief キャラクターの当たり判定を管理するコンポーネントクラス
///
/// @tparam TOwner コンポーネントを所有するクラスの型
template<typename TOwner>
class CollisionComponent : public IComponent<TOwner>
{
public:

	virtual ~CollisionComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	/// 
	/// @return 成功しているならtrue、失敗しているならfalse
	bool Initialize(TOwner& owner) override
	{
		// コンポーネントの所有者を設定する
		IComponent<TOwner>::Initialize(owner);

		return true; 
	}

	/// @brief 初期化関数
	///
	/// @param owner 初期化処理を行うキャラクター
	void Update(TOwner& owner) override {}

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 判定を有効にする関数
	///
	/// @param colData 当たり判定のデータ
	void ActiveCollision(const CollisionData& colData)
	{
		m_collisionData = colData;
		m_isActive = true;
	}

	/// @brief 判定を無効にする関数
	void DeactiveCollision()
	{
		m_isActive = false;
	}

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 当たり判定のデータを取得する関数
	///
	/// @return 当たり判定のデータ
	const CollisionData& GetCollisionData() const { return m_collisionData; }

	/// @brief 当たり判定が有効かどうかを取得する関数
	///
	/// @return 当たり判定が有効かどうか、有効である場合はtrue、そうでない場合はfalse
	bool IsActive() const { return m_isActive; }

protected:

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 当たり判定のデータ
	CollisionData m_collisionData;

	/// 当たり判定が有効かどうか
	bool m_isActive = false;

};