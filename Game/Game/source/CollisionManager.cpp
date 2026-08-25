#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "ActionAttack.h"
#include "HealthComponent.h"
#include "DamageComponent.h"
#include "GravityComponent.h"
#include "Character.h"
#include "Collision/DxLibCollisionMath.h"
#include "CollisionShapeBuilder.h"
#include "DamageConverter.h"

#include "Collision/HitCollision.h"

void CollisionManager::Update(const std::vector<Character*>& characters)
{
	// 簡易的な仮実装
	// キャラクターが床にめり込んでいる場合、床の高さに修正する
	for(auto* character : characters)
	{
		if(!character) { continue; }
		ResolveCharacterFloorPenetration(character);
	}



	//===========================================================================
	// キャラクター同士の当たり判定
	//===========================================================================

	// 判定用に、キャラクターを二重ループで回す
	for(size_t i = 0; i < characters.size(); ++i)
	{
		// キャラクター1を取得
		Character* character1 = characters[i];
		if(!character1) { continue; }

		// +1 しているのは、キャラクター同士の衝突判定は一度だけ行えばよいから
		for(size_t j = i + 1; j < characters.size(); ++j)
		{
			// キャラクター2を取得
			Character* character2 = characters[j];
			if(!character2) { continue; }

			// キャラクター同士の衝突判定を行う
			auto collision = CheckHitCharacter(character1, character2);

			// キャラクター同士がヒットしたなら
			if(collision.isHit)
			{
				// キャラクター同士が衝突したときの押し出し処理を行う
				ResolveCharacterCollision(character1, character2, collision);

				// キャラクター同士がヒットしたときの処理を行う
				HitCharacterProcess(character1, character2);
			}
		}
	}

	//===========================================================================
	// 攻撃の当たり判定
	//===========================================================================

	// 判定用に、キャラクターを二重ループで回す
	for(auto* attacker : characters)
	{
		if(!attacker) { continue; }

		for(auto* defender : characters)
		{
			if(!defender) { continue; }

			// 同じキャラである場合はスキップ
			if(attacker == defender) { continue; }

			// 攻撃
			{
				// 攻撃がヒットしたなら
				if(CheckHitAttack(attacker, defender))
				{
					// 攻撃ヒット時の処理を行う
					HitAttackProcess(attacker, defender);
				}
			}
		}
	}
}

void CollisionManager::ResolveCharacterFloorPenetration(Character* character)
{
	if(!character) { return; }

	// キャラクターのオブジェクトデータを取得
	ObjectData data = character->GetObjectData();

	// キャラクターのY座標が床合すり抜け対策の高さより下にある場合
	if(data.pos.GetY() < 0.0f)
	{
		// キャラクターのY座標を床合すり抜け対策の高さに修正
		data.pos.SetY(0.0f);

		// キャラクターの重力コンポーネントを取得
		auto gravityComp = character->GetComponent<GravityComponent<Character>>();
		if(gravityComp)
		{
			// Y方向の速度を0に設定
			gravityComp->SetVelocityY(0.0f);
		}

		// 修正したオブジェクトデータをキャラクターに設定
		character->SetObjectData(data);
	}
}

HitCheck::CapsuleCollisionResult CollisionManager::CheckHitCharacter(Character* character1, Character* character2)
{
	HitCheck::CapsuleCollisionResult result;

	// キャラクター1のカプセル形状を作成
	auto capsule1 = CollisionShapeBuilder::CreateCharacterCapsule(*character1);
	if(!capsule1.has_value()) { return result; }

	// キャラクター2のカプセル形状を作成
	auto capsule2 = CollisionShapeBuilder::CreateCharacterCapsule(*character2);
	if(!capsule2.has_value()) { return result; }

	// カプセル同士の衝突時の計算結果を返す
	return HitCheck::CapsuleToCapsule(capsule1.value(), capsule2.value());
}

void  CollisionManager::ResolveCharacterCollision(
	Character* character1,
	Character* character2,
	const HitCheck::CapsuleCollisionResult& collision)
{
	if(!collision.isHit || collision.penetration <= 0.0f) { return; }

	// 衝突の貫通深さを0.25倍にして、押し出しの量を調整する
	const Vec3::Vector3 correction = collision.normal * (collision.penetration * 0.25f);

	ObjectData data1 = character1->GetObjectData();
	ObjectData data2 = character2->GetObjectData();

	// キャラクター1の位置を修正
	// 減算なのは、キャラクター1の法線ベクトルがキャラクター2の方向を向いているため
	data1.pos -= correction;
	
	// キャラクター2の位置を修正
	// 加算なのは、キャラクター2の法線ベクトルがキャラクター1の方向を向いているため
	data2.pos += correction;

	character1->SetObjectData(data1);
	character2->SetObjectData(data2);
}

void CollisionManager::HitCharacterProcess(Character* character1, Character* character2)
{
	printfDx("キャラクター同士がヒットしました！\n");
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

	// 攻撃コリジョンと防御者の衝突フラグを返す
	return HitCheck::CapsuleToCapsule(attackCapsule.value(), defCapsule.value()).isHit;
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