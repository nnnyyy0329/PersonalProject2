#pragma once
#include "Collision/HitCollision.h"
#include "math/Math.h"
#include <vector>

class Character;	/// キャラクタークラス

/// @brief 当たり判定を管理するクラス
class CollisionManager
{
public:

	CollisionManager() = default;
	virtual ~CollisionManager() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 当たり判定の更新関数
	///
	/// @param characters 当たり判定を更新するキャラクターのリスト
	/// @param wallColliders 壁の当たり判定用のAABBリスト
	void Update(const std::vector<Character*>& characters, const std::vector<Math::AABB>& wallColliders);

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief 簡易的なキャラの床合すり抜け対策関数
	///
	/// @param character 床合すり抜け対策を行うキャラクター
	void ResolveCharacterFloorPenetration(Character* character);

	/// @brief キャラクターと壁の衝突判定を行う関数
	///
	/// @param character 衝突判定を行うキャラクター
	/// @param wallColliders 壁の当たり判定用のAABBリスト
	void ResolveCharacterWallCollision(
		Character* character, const std::vector<Math::AABB>& wallColliders);

	/// @brief キャラクターを床の範囲内に制限する関数
	///
	/// @param character 床の範囲内に制限するキャラクター
	void ClampCharacterToFloor(Character* character);

	/// @brief キャラクター同士がヒットしたかどうかを判定する関数
	///
	/// @param character1 キャラクター1
	/// @param character2 キャラクター2
	/// 
	/// @return ヒット結果を含む構造体
	HitCheck::CapsuleCollisionResult CheckHitCharacter(Character* character1, Character* character2);

	/// @brief キャラクター同士が衝突したときの押し出し処理を行う関数
	///
	/// @param character1 キャラクター1
	/// @param character2 キャラクター2
	/// @param collision キャラクター同士の衝突判定結果
	void ResolveCharacterCollision(
		Character* character1, 
		Character* character2, 
		const HitCheck::CapsuleCollisionResult& collision);

	/// @brief キャラクター同士がヒットしたときの処理を行う関数
	///
	/// @param character1 キャラクター1
	/// @param character2 キャラクター2
	void HitCharacterProcess(Character* character1, Character* character2);

	/// @brief 攻撃がヒットしたかどうかを判定する関数
	///
	/// @param attacker 攻撃を行ったキャラクター
	/// @param defender 攻撃を受けたキャラクター
	/// 
	/// @return 攻撃がヒットした場合はtrue、そうでない場合はfalse
	bool CheckHitAttack(Character* attacker, Character* defender);

	/// @brief 攻撃がヒットしたかどうかを判定する関数
	///
	/// @param attacker 攻撃を行ったキャラクター
	/// @param defender 攻撃を受けたキャラクター
	/// 
	/// @return ヒット結果を含む構造体
	HitCheck::CapsuleCollisionResult CheckHitAttackCapsule(Character* attacker, Character* defender);

	/// @brief 攻撃がヒットしたときの処理を行う関数
	///
	/// @param attacker 攻撃を行ったキャラクター
	/// @param defender 攻撃を受けたキャラクター
	void HitAttackProcess(Character* attacker, Character* defender);

};

