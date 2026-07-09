#include "EnemyIdleState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyIdleState::Enter(Enemy& owner)
{
	// 敵のアニメーションコンポーネントを取得
	auto enemyAnimComp = owner.GetComponent<EnemyAnimationComponent>();
	if(!enemyAnimComp) { return; }

	// 敵のアニメーションをアイドル状態に設定
	enemyAnimComp->PlayAnimIdle();
}

void EnemyIdleState::Update(Enemy& owner)
{

}

void EnemyIdleState::Exit(Enemy& owner)
{

}