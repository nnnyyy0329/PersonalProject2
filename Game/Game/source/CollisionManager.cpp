#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "Character.h"
#include "HealthComponent.h"
#include "Collision/DxLibCollisionMath.h"

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

	// 防御者の当たり判定コンポーネントを取得
	auto* defCol = defender->GetComponent<CollisionComponent<Character>>();
	if(!defCol) { return false; }

	// 当たり判定のデータを取得
	const auto& attackData = attackCol->GetCollisionData();
	const auto& defData = defCol->GetCollisionData();

	// 攻撃者の位置を取得
	VECTOR attackerPos = attacker->GetObjectData().pos;

	// 防御者の位置と当たり判定データを取得
	VECTOR defenderPos = defender->GetObjectData().pos;
	auto defenderCharCol = defender->GetCharColData();

	// 攻撃者の攻撃判定
	DxLibCollisionMath::Capsule attackCapsule;
	attackCapsule.top = VAdd(attackerPos, attackData.offset);
	attackCapsule.bottom = attackerPos;
	attackCapsule.radius = attackData.radius;

	// 防御者の当たり判定
	DxLibCollisionMath::Capsule defCapsule;
	defCapsule.top = VAdd(defenderPos, defenderCharCol.top);
	defCapsule.bottom = VAdd(defenderPos, defenderCharCol.bottom);
	defCapsule.radius = defenderCharCol.radius;

	// カプセル同士の当たり判定を行う
	if(DxLibCollisionMath::CheckCapsuleToCapsule(attackCapsule, defCapsule))
	{
		return true;
	}

	return false;
}