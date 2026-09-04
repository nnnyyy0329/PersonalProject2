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
#include "Server/SoundServer.h"
#include "math/Math.h"
#include "MapData.h"

void CollisionManager::Update(
	const std::vector<Character*>& characters, const std::vector<Math::AABB>& wallColliders)
{
	//===========================================================================
	// マップとキャラの判定
	//===========================================================================

	for(auto* character : characters)
	{
		if(!character) { continue; }

		// 簡易的な実装
		// キャラクターが床にめり込んでいる場合、床の高さに修正する
		ResolveCharacterFloorPenetration(character);

		// キャラクターが床の範囲外に出ないように制限する
		ClampCharacterToFloor(character);

		// キャラクターと壁の衝突判定を行う
		ResolveCharacterWallCollision(character, wallColliders);
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

	auto gravityComp = character->GetComponent<GravityComponent<Character>>();
	if(!gravityComp) { return; }

	// キャラクターのカプセルを作成
	auto capsule = CollisionShapeBuilder::CreateCharacterCapsule(*character);
	if(!capsule.has_value()) { return; }

	// キャラクターのカプセルを取得
	auto& charCapsule = capsule.value();

	// 床の高さを定数として定義
	constexpr float floorY = 0.0f;

	// カプセルの一番下のY座標
	float capsuleBottom =
		Math::Min(charCapsule.start.GetY(), charCapsule.end.GetY()) - charCapsule.radius;

	// 床より下にめり込んでいなければ何もしない
	if(capsuleBottom >= floorY) { return; }

	// 床まで押し上げる量
	float correction = floorY - capsuleBottom;

	ObjectData correctedData = character->GetObjectData();

	// キャラクターを上方向へ押し出す
	correctedData.pos.SetY(correctedData.pos.GetY() + correction);

	character->SetObjectData(correctedData);

	// 落下速度を止める
	gravityComp->SetVelocityY(0.0f);
}

void CollisionManager::ResolveCharacterWallCollision(
	Character* character, const std::vector<Math::AABB>& wallColliders)
{
	if(!character)
	{
		return;
	}

	for(const auto& wall : wallColliders)
	{
		auto capsule =
			CollisionShapeBuilder::CreateCharacterCapsule(
				*character);

		if(!capsule.has_value())
		{
			continue;
		}

		auto collision =
			HitCheck::CapsuleToAABB(
				capsule.value(),
				wall);

		if(!collision.isHit ||
		   collision.penetration <= 0.0f)
		{
			continue;
		}

		ObjectData data =
			character->GetObjectData();

		data.pos +=
			collision.normal * collision.penetration;

		character->SetObjectData(data);
	}


	//if(!character) { return; }

	//// キャラクターのカプセルを作成
	//auto capsule = CollisionShapeBuilder::CreateCharacterCapsule(*character);
	//if(!capsule.has_value()) { return; }

	//for(auto& wall : wallColliders)
	//{
	//	// キャラクターのカプセルと壁のAABBの衝突判定を行う
	//	auto collision = HitCheck::CapsuleToAABB(capsule.value(), wall);

	//	// 衝突していない場合はスキップ
	//	if(!collision.isHit || collision.penetration <= 0.0f) { continue; }

	//	ObjectData data = character->GetObjectData();

	//	// キャラクターを押し出す
	//	data.pos += collision.normal * collision.penetration;

	//	character->SetObjectData(data);
	//}
}

void CollisionManager::ClampCharacterToFloor(Character* character)
{
	if(!character) { return; }

	// キャラクターのカプセルを作成
	auto capsule = CollisionShapeBuilder::CreateCharacterCapsule(*character);
	if(!capsule.has_value()) { return; }

	// キャラクターのカプセルを取得
	auto& charCapsule = capsule.value();

	// X軸方向とZ軸方向の床の範囲を計算
	constexpr float floorWidth =
		static_cast<float>(MapData::PLANE_SIZE) * static_cast<float>(MapData::PLANE_TILE_X);
	constexpr float floorDepth =
		static_cast<float>(MapData::PLANE_SIZE) * static_cast<float>(MapData::PLANE_TILE_Z);

	// 床の半分の幅と奥行きを計算
	constexpr float floorHalfWidth = floorWidth * 0.5f;
	constexpr float floorHalfDepth = floorDepth * 0.5f;

	// キャラのカプセルが、床内に収まる範囲の計算
	float minX = -floorHalfWidth + charCapsule.radius;
	float maxX =  floorHalfWidth - charCapsule.radius;
	float minZ = -floorHalfDepth + charCapsule.radius;
	float maxZ =  floorHalfDepth - charCapsule.radius;

	ObjectData data = character->GetObjectData();

	// X軸方向とZ軸方向を床の範囲内に収まるように補正
	float correctedX = Math::Clamp(data.pos.GetX(), minX, maxX);
	float correctedZ = Math::Clamp(data.pos.GetZ(), minZ, maxZ);

	// 座標が変わったときだけ反映
	if(data.pos.GetX() != correctedX || data.pos.GetZ() != correctedZ)
	{
		// 座標を補正してキャラクターに設定
		data.pos.SetX(correctedX);
		data.pos.SetZ(correctedZ);
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

	// 攻撃ヒット時のサウンドを再生する
	auto ss = SoundServer::GetInstance();
	ss->Play(attackData.soundData.name2, DX_PLAYTYPE_BACK);

	// 変換したダメージ情報をダメージコンポーネントに設定
	damageComp->SetDamageInfo(damageInfo);

	// ダメージを適用する
	float damage = actionAttack->GetAttackData().damageData.damage;
	healthComp->ApplyDamage(damageInfo);
}