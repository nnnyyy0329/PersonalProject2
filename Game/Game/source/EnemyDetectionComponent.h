#pragma once
#include "IComponent.h"
#include "math/Math.h"
#include <cmath>

/// 敵の検知範囲関連の名前空間
namespace Detection
{
	constexpr float DETECT_RANGE		= 350.0f;	// 未発見から発見までの索敵範囲
	constexpr float LOSE_RANGE			= 500.0f;	// 発見から見失うまでの範囲
	constexpr float ATTACK_START_RANGE	= 150.0f;	// 攻撃範囲
	const float ThresholdAngle			= std::cos(15.0f * Math::PI_VALUE / 180.0f);	// 攻撃範囲の前方向の角度
}

class Character;	/// キャラクタークラス

/// @brief 敵の検知コンポーネントクラス
class EnemyDetectionComponent : public IComponent<Character>
{
public:

	EnemyDetectionComponent() = default;
	virtual ~EnemyDetectionComponent() = default;

	//===========================================================================
	// 基本関数
	//===========================================================================

	/// @brief 敵の検知処理を行う関数
	///
	/// @param owner 検知処理を行う敵
	/// @param gameContext 更新処理に必要なゲームコンテキスト
	virtual void Update(Character& owner, const GameContext& gameContext) override;

	//===========================================================================
	// ターゲット関連関数
	//===========================================================================

	/// @brief 検知対象のキャラクターを取得する関数
	///
	/// @return 検知対象のキャラクターのポインタ。検知対象がいない場合はnullptr
	Character* GetTarget() const { return m_target; }

	/// @brief 検知対象のキャラクターがいるかどうかを判定する関数
	///
	/// @return 検知対象がいる場合はtrue、いない場合はfalse
	bool HasTarget() const { return m_target != nullptr; }

	//===========================================================================
	// 攻撃関連関数
	//===========================================================================

	/// @brief ターゲットが攻撃開始範囲内にいて、攻撃を開始できるか
	///
	/// @param owner 攻撃を開始する敵
	/// 
	/// @return 開始できるならtrue、開始できないならfalse
	bool CanStartAttack(const Character& owner) const;

	//===========================================================================
	// ゲッター
	//===========================================================================

	/// @brief 検知範囲の取得関数
	///
	/// @return 検知範囲の値
	float GetDetectRange() const { return Detection::DETECT_RANGE; }

	/// @brief 見失う範囲の取得関数
	///
	/// @return 見失う範囲の値
	float GetLoseRange() const { return Detection::LOSE_RANGE; }

	/// @brief 攻撃範囲の取得関数
	///
	/// @return 攻撃範囲の値
	float GetAttackRange() const { return Detection::ATTACK_START_RANGE; }

private:

	//===========================================================================
	// 内部関数
	//===========================================================================

	/// @brief ターゲット変更の更新を行う関数
	void UpdateTarget(Character& owner, const GameContext& gameContext);

	/// @brief 検知対象のキャラクターが指定の範囲内にいるかどうかを判定する関数
	///
	/// @param owner 検知処理を行う敵
	/// @param target 検知対象のキャラクター
	/// 
	/// @return 範囲内にいるならtrue、範囲外ならfalse
	bool IsTargetInDetectionRange(const Character& owner, const Character& target) const;

	/// @brief 攻撃対象のキャラクターが指定の攻撃範囲内にいるかどうかを判定する関数
	///
	/// @param owner 攻撃処理を行う敵
	/// @param target 攻撃対象のキャラクター
	/// 
	/// @return 攻撃範囲内にいるならtrue、範囲外ならfalse
	bool IsTargetInAttackRange(const Character& owner, const Character& target) const;

	/// @brief 攻撃対象のキャラクターが指定の攻撃範囲内にいて、かつ敵の前方向にいるかどうかを判定する関数
	///
	/// @param owner 攻撃処理を行う敵
	/// 
	/// @return 攻撃範囲内にいて、かつ敵の前方向にいるならtrue、そうでないならfalse
	bool IsTargetInFacingRange(const Character& owner, const Character& target) const;

	//===========================================================================
	// メンバ変数
	//===========================================================================

	/// 検知対象のキャラクター
	Character* m_target = nullptr;

};

