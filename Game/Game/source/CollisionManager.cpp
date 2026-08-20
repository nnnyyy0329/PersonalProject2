#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "ActionAttack.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "Character.h"
#include "Collision/DxLibCollisionMath.h"
#include "CollisionShapeBuilder.h"
#include "DamageConverter.h"

#include "Collision/HitCollision.h"

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
				// 攻撃がヒットしたときの処理を行う
				HitAttackProcess(attacker, defender);
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

	//// カプセル同士の当たり判定を行う
	//if(DxLibCollisionMath::CheckCapsuleToCapsule(attackCapsule.value(), defCapsule.value()))
	//{
	//	return true;
	//}

	if(HitCheck::CapsuleToCapsule(attackCapsule.value(), defCapsule.value()))
	{
		return true;
	}

	return false;
}



#include "Server/SoundServer.h"



void CollisionManager::HitAttackProcess(Character* attacker, Character* defender)
{
	// 攻撃者の攻撃コンポーネントを取得する
	auto* actionAttack = attacker->GetCurrentAction<ActionAttack>();
	if(!actionAttack) { return; }

	// 防御者の体力コンポーネントを取得する
	auto* healthComp = defender->GetComponent<HealthComponent<Character>>();
	if(!healthComp || healthComp->IsDead()) { return; }

	// 防御者のダメージコンポーネントを取得する
	auto* damageComp = defender->GetComponent<DamageComponent<Character>>();
	if(!damageComp) { return; }

	// 攻撃がすでにヒットしたキャラならスキップ
	if(actionAttack->HasHitCharacter(defender)) { return; }

	// ヒットしたキャラではないなら、攻撃がヒットしたキャラとして登録する
	actionAttack->RegisterHitCharacter(defender);




	printfDx("攻撃がヒットしました！\n");




	// 攻撃データを取得する
	const AttackData& attackData = actionAttack->GetAttackData();

	// ダメージ情報を取得し、攻撃データとヒット方向をダメージデータに変換
	Vec3::Vector3 dir = defender->GetObjectData().pos - attacker->GetObjectData().pos;
	dir.SetY(0.0f);
	DamageInfo damageInfo = DamageConverter::ConvertAttackDataToDamageInfo(attackData, dir.Normalize());




	auto ss = SoundServer::GetInstance();
	ss->Play(attackData.soundData.name2, DX_PLAYTYPE_BACK);




	// 変換したダメージ情報をダメージコンポーネントに設定
	damageComp->SetDamageInfo(damageInfo);

	// ダメージを適用する
	float damage = actionAttack->GetAttackData().damageData.damage;
	healthComp->ApplyDamage(damageInfo);
}