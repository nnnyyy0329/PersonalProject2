#include "EnemyAttackComponent.h"
#include "Character.h"
#include "ActionAttack.h"
#include "GravityComponent.h"

EnemyAttackComponent::EnemyAttackComponent()
{
	AttackData step1;
	step1.timing.startTime					= 50.0f;
	step1.timing.activeDuration				= 7.0f;
	step1.timing.recoveryDuration			= 50.5f;
	step1.timing.comboReceiveTime			= 0.0f;
	step1.timing.isAutoNextAttack			= false;
	step1.colData.shape						= ShapeType::CAPSULE;
	step1.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
	step1.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
	step1.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
	step1.colData.radius					= 50.0f;
	step1.damageData.damage					= 0.1f;
	step1.damageData.hitStunTime			= 0.0f;
	step1.damageData.damageInvincibeTime	= 0.0f;
	step1.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	step1.knockbackData.knockbackSpeed		= 0.0f;
	step1.knockbackData.knockbackTime		= 30.0f;
	step1.moveData.movePhase				= AttackPhase::STARTUP;
	step1.moveData.moveSpeed				= 3.0f;
	step1.moveData.moveTime					= 5.0f;
	step1.effectData.name					= "EF_Attack";
	step1.soundData.name1					= "SE_SwingAttack";
	step1.soundData.name2					= "SE_Attack1";
	step1.cameraShakeData.duration			= 60.0f;
	step1.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(step1);

}

void EnemyAttackComponent::Update(Character& owner, const GameContext& gameContext)
{
	if(m_cooldown > 0.0f)
	{
		m_cooldown -= 1.0f;
	}
}

bool EnemyAttackComponent::TryAttack(Character& owner)
{
	// 現在のアクションが攻撃アクションである場合、攻撃を行わない
	if(owner.IsCurrentAction<ActionAttack>()){ return false; }

	if(m_attackDataList.empty()){ return false; }

	// 攻撃アクションを設定する
	owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[0]));

	// 攻撃のクールダウンをリセットする
	m_cooldown = Attack::COOLDOWN;

	return true;
}