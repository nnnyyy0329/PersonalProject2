#include "EnemyDeathState.h"
#include "Enemy.h"
#include "EnemyAnimationComponent.h"

void EnemyDeathState::Enter(Enemy& owner)
{
	// アニメーションコンポーネントを取得
	auto animationComp = owner.GetComponent<EnemyAnimationComponent>();
	if(animationComp) { animationComp->PlayAnimDeath(); }
}

void EnemyDeathState::Update(Enemy& owner)
{
	
}

void EnemyDeathState::Exit(Enemy& owner)
{

}