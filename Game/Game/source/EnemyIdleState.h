#pragma once
#include "IState.h"

class Enemy;					/// 敵クラス
class EnemyAnimationComponent;	/// 敵のアニメーションコンポーネントクラス

/// @brief 敵のアイドルステートクラス
class EnemyIdleState : public IState<Enemy>
{
public:

	EnemyIdleState() = default;
	virtual ~EnemyIdleState() = default;

	//===========================================================================	
	// 内部関数
	//===========================================================================

	/// @brief ステートに入ったときに呼ばれる関数
	///
	/// @param owner ステートに入ったオーナー
	virtual void Enter(Enemy& owner) override;
	/// @brief ステート中の更新関数
	///
	/// @param owner ステート中の更新処理を行うオーナー
	virtual void Update(Enemy& owner) override;
	/// @brief ステートから抜けるときに呼ばれる関数
	///
	/// @param owner ステートから抜けるオーナー
	virtual void Exit(Enemy& owner) override;

private:

	//===========================================================================	
	// メンバ変数
	//===========================================================================

	/// 敵のアニメーションコンポーネントの参照用ポインタ
	EnemyAnimationComponent* m_enemyAnimComponent = nullptr;

};

