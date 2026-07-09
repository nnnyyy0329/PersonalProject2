#include "EnemyMoveState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyMoveState::Enter(Enemy& owner)
{
	// 敵のアニメーションコンポーネントを取得
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(!enemyAnimComp) { return; }

	// 敵のアニメーションを移動状態に設定
	enemyAnimComp->PlayAnimMove();
}

void EnemyMoveState::Update(Enemy& owner)
{

}

void EnemyMoveState::Exit(Enemy& owner)
{

}
