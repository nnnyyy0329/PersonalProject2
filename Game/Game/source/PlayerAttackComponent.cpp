#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData step1;
    step1.timing.startTime					= 16.0f;
    step1.timing.activeDuration				= 5.0f;
    step1.timing.recoveryDuration			= 9.0f;
    step1.timing.comboReceiveTime			= 1.0f;
	step1.timing.isAutoNextAttack			= false;
	step1.colData.shape						= ShapeType::CAPSULE;
	step1.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
	step1.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
	step1.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
	step1.colData.radius					= 50.0f;
	step1.damageData.damage					= 30.0f;
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

	AttackData step2;
    step2.timing.startTime					= 10.0f;
    step2.timing.activeDuration				= 3.0f;
    step2.timing.recoveryDuration			= 14.0f;
    step2.timing.comboReceiveTime			= 1.0f;
	step2.timing.isAutoNextAttack			= false;
	step2.colData.shape						= ShapeType::CAPSULE;
	step2.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    step2.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    step2.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    step2.colData.radius					= 50.0f;
	step2.damageData.damage					= 30.0f;
	step2.damageData.hitStunTime			= 0.0f;
	step2.damageData.damageInvincibeTime	= 0.0f;
	step2.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	step2.knockbackData.knockbackSpeed		= 0.0f;
	step2.knockbackData.knockbackTime		= 30.0f;
	step2.moveData.movePhase				= AttackPhase::STARTUP;
	step2.moveData.moveSpeed				= 0.0f;
	step2.moveData.moveTime					= 0.0f;
	step2.effectData.name					= "EF_Attack";
	step2.soundData.name1					= "SE_SwingAttack";
	step2.soundData.name2					= "SE_Attack2";
	step2.cameraShakeData.duration			= 60.0f;
	step2.cameraShakeData.magnitude			= 10.0f;
    AddAttackData(step2);

    AttackData step3;
    step3.timing.startTime					= 4.0f;
    step3.timing.activeDuration				= 7.0f;
    step3.timing.recoveryDuration			= 19.0f;
    step3.timing.comboReceiveTime			= 16.0f;
	step3.timing.isAutoNextAttack			= true;
	step3.colData.shape						= ShapeType::CAPSULE;
	step3.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    step3.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    step3.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    step3.colData.radius					= 50.0f;
	step3.damageData.damage					= 45.0f;
	step3.damageData.hitStunTime			= 0.0f;
	step3.damageData.damageInvincibeTime	= 0.0f;
	step3.knockbackData.moveDirection		= { 0.0f, 1.0f, 0.0f };
	step3.knockbackData.knockbackSpeed		= 7.0f;
	step3.knockbackData.knockbackTime		= 30.0f;
	step3.moveData.movePhase				= AttackPhase::ALL;
	step3.moveData.moveSpeed				= 2.0f;
	step3.moveData.moveTime					= 27.0f;
	step3.effectData.name					= "EF_Attack";
	step3.soundData.name1					= "SE_SwingAttack";
	step3.soundData.name2					= "SE_Attack3";
	step3.cameraShakeData.duration			= 60.0f;
	step3.cameraShakeData.magnitude			= 10.0f;
    AddAttackData(step3);

	AttackData step4;
	step4.timing.startTime					= 11.0f;
	step4.timing.activeDuration				= 9.0f;
	step4.timing.recoveryDuration			= 20.0f;
	step4.timing.comboReceiveTime			= 1.0f;
	step4.timing.isAutoNextAttack			= false;
	step4.colData.shape						= ShapeType::CAPSULE;
	step4.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    step4.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    step4.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    step4.colData.radius					= 50.0f;
	step4.damageData.damage					= 55.0f;
	step4.damageData.hitStunTime			= 0.0f;
	step4.damageData.damageInvincibeTime	= 0.0f;
	step4.knockbackData.moveDirection		= { 0.0f, -2.0f, 0.0f };
	step4.knockbackData.knockbackSpeed		= 7.0f;
	step4.knockbackData.knockbackTime		= 30.0f;
	step4.moveData.movePhase				= AttackPhase::ALL;
	step4.moveData.moveSpeed				= 2.0f;
	step4.moveData.moveTime					= 21.0f;
	step4.effectData.name					= "EF_Attack";
	step4.soundData.name1					= "SE_SwingAttack";
	step4.soundData.name2					= "SE_Attack3";
	step4.cameraShakeData.duration			= 60.0f;
	step4.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(step4);

	AttackData step5;
	step5.timing.startTime					= 30.0f;
	step5.timing.activeDuration				= 25.0f;
	step5.timing.recoveryDuration			= 0.0f;
	step5.timing.comboReceiveTime			= 0.0f;
	step5.timing.isAutoNextAttack			= false;
	step5.colData.shape						= ShapeType::CAPSULE;   
	step5.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    step5.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    step5.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    step5.colData.radius					= 50.0f;
	step5.damageData.damage					= 100.0f;
	step5.damageData.hitStunTime			= 0.0f;
	step5.damageData.damageInvincibeTime	= 0.0f;
	step5.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	step5.knockbackData.knockbackSpeed		= 2.0f;
	step5.knockbackData.knockbackTime		= 30.0f;
	step5.moveData.movePhase				= AttackPhase::ACTIVE;
	step5.moveData.moveSpeed				= 4.0f;
	step5.moveData.moveTime					= 25.0f;
	step5.effectData.name					= "EF_Attack";
	step5.soundData.name1					= "SE_SwingAttack";
	step5.soundData.name2					= "SE_Attack3";
	step5.cameraShakeData.duration			= 60.0f;
	step5.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(step5);
}

void PlayerAttackComponent::Update(Character& owner, const GameContext& gameContext)
{
	auto* currentAction = owner.GetCurrentAction<ActionAttack>();

	// 現在のアクションが攻撃アクションである場合
	if(currentAction)
	{
		// 現在のコンボインデックス
		// m_comboIndexは次の攻撃のインデックスを指しているため、現在の攻撃のインデックスはm_comboIndex - 1
		int currentComboIndex = m_comboIndex - 1;

		// 現在のコンボインデックスが有効範囲内である場合
		if(IsVaildCurrentComboIndex(currentComboIndex))
		{
			// 現在の攻撃データの「次に自動でつながる」フラグが立っており、かつコンボ受付中である場合
			if(m_attackDataList[currentComboIndex].timing.isAutoNextAttack && currentAction->IsCancelable())
			{
				// 自動コンボを発動する
				AutoCombo(owner);
			}
		}
	}
	// 攻撃アクションが終了している場合
	else
	{
		// コンボをリセットする
		ResetCombo();
	}
}

bool PlayerAttackComponent::TryAttack(Character& owner)
{
	// 現在のアクションが攻撃アクションでない場合
	if(!owner.IsCurrentAction<ActionAttack>())
	{
		// コンボ攻撃が有効範囲内の場合
		if(IsValidComboIndex())
		{
			// 攻撃アクションを設定する
			owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[m_comboIndex]));
			m_comboIndex++;


			printfDx("攻撃入力が処理されました\n");


			return true;
		}
	}

	// 現在のアクションが攻撃アクションであり、コンボ受付中なら
	auto* currentAction = owner.GetCurrentAction<ActionAttack>();
	if(currentAction && currentAction->IsCancelable())
	{
		// コンボ攻撃が有効範囲内の場合
		if(IsValidComboIndex())
		{
			// 攻撃アクションを設定する
			owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[m_comboIndex]));
			m_comboIndex++;


			printfDx("コンボ攻撃入力が処理されました\n");


			return true;
		}
	}

	return false;
}

void PlayerAttackComponent::AutoCombo(Character& owner)
{
	// コンボ攻撃が有効範囲内の場合
	if(IsValidComboIndex())
	{
		// 次の攻撃を自動で発動する
		owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[m_comboIndex]));
		m_comboIndex++;

		printfDx("自動コンボが発動しました\n");
	}
}

bool PlayerAttackComponent::IsValidComboIndex() const
{
	return m_comboIndex >= 0 && m_comboIndex < m_attackDataList.size();
}

bool PlayerAttackComponent::IsVaildCurrentComboIndex(int comboIndex) const
{
	return comboIndex >= 0 && comboIndex < m_attackDataList.size();
}