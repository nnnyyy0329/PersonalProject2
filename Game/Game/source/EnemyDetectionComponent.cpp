#include "EnemyDetectionComponent.h"
#include "Character.h"
#include "GameContext.h"
#include "ObjectManager.h"
#include "Player.h"
#include "JudgementMath.h"
#include "GeometryUtility/GeometryUtility.h"

void EnemyDetectionComponent::Update(Character& owner, const GameContext& gameContext)
{
	// ターゲットの更新を行う
	UpdateTarget(owner, gameContext);
}

void EnemyDetectionComponent::UpdateTarget(Character& owner, const GameContext& gameContext)
{
	// プレイヤーオブジェクトを取得
	auto* player = gameContext.GetObjectManager().GetPlayer();
	if(!player)
	{
		m_target = nullptr;
		return;
	}

	// プレイヤーが指定の範囲内にいるかどうかを判定
	if(IsTargetInDetectionRange(owner, *player))
	{
		// すでに同じターゲットであれば、ターゲットを変更しない
		if(m_target == player){ return; }

		m_target = player;
	}
	else
	{
		m_target = nullptr;
	}
}

bool EnemyDetectionComponent::IsTargetInDetectionRange(const Character& owner, const Character& target) const
{
	// 検知対象がすでにいる場合は、LOSE_RANGEを使用し、いない場合はDETECT_RANGEを使用
	float range = m_target ? Detection::LOSE_RANGE : Detection::DETECT_RANGE;

	// 2人のキャラクター間の距離が指定の範囲内にあるかどうかを判定
	return JudgementMath::IsCharacterInRange(owner, target, range);
}

bool EnemyDetectionComponent::IsTargetInAttackRange(const Character& owner, const Character& target) const
{
	// 2人のキャラクター間の距離が攻撃範囲内にあるかどうかを判定
	return JudgementMath::IsCharacterInRange(owner, target, Detection::ATTACK_START_RANGE);
}

bool EnemyDetectionComponent::CanStartAttack(const Character& owner) const
{
	if(!m_target){ return false; }

	// ターゲットが攻撃範囲内にいるかどうかを判定
	bool inAttackRange = IsTargetInAttackRange(owner, *m_target);

	// ターゲットが前方にいるかどうかを判定
	bool inFacingRange = IsTargetInFacingRange(owner, *m_target);

	return inAttackRange && inFacingRange;
}

bool EnemyDetectionComponent::IsTargetInFacingRange(const Character& owner, const Character& target) const
{
	// ターゲットが前方にいるかどうかを判定
	return GeometryUtility::IsFacing(
		owner.GetObjectData().pos, 
		owner.GetForward(),
		target.GetObjectData().pos, 
		Detection::ThresholdAngle);
}