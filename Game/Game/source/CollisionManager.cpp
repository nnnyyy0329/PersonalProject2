#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "Character.h"
#include "HealthComponent.h"
#include "Collision/DxLibCollisionMath.h"
#include "CollisionShapeBuilder.h"

void CollisionManager::Update(const std::vector<Character*>& characters)
{
	// 攻撃者のキャラ
	for(auto* attacker : characters)
	{
		if(!attacker) { continue; }

		// 防御者のキャラ
		for(auto* defender : characters)
		{
			if(!defender) { continue; }

			// 攻撃者と防御者が同じキャラである場合はスキップ
			if(attacker == defender) { continue; }

			// 攻撃がヒットしたかどうかを判定する
			if(CheckHitAttack(attacker, defender))
			{
				// 防御者の体力コンポーネントを取得する
				auto* healthComp = defender->GetComponent<HealthComponent<Character>>();
				if(!healthComp || healthComp->IsDead()) { continue; }

				// ダメージを適用する
				healthComp->ApplyDamage(0.5f);



				printfDx("攻撃がヒットしました！\n");
			}
		}
	}
}

bool CollisionManager::CheckHitAttack(Character* attacker, Character* defender)
{
	// 攻撃者の当たり判定コンポーネントを取得
	auto* attackCol = attacker->GetComponent<CollisionComponent<Character>>();
	if(!attackCol || !attackCol->IsActive()) { return false; }

	// 攻撃者の攻撃判定
	auto attackCapsule = CollisionShapeBuilder::CreateAttackCapsule(*attacker);
	if(!attackCapsule.has_value()) { return false; }

	// 防御者の当たり判定
	auto defCapsule = CollisionShapeBuilder::CreateCharacterCapsule(*defender);
	if(!defCapsule.has_value()) { return false; }

	// カプセル同士の当たり判定を行う
	if(DxLibCollisionMath::CheckCapsuleToCapsule(attackCapsule.value(), defCapsule.value()))
	{
		return true;
	}

	return false;
}