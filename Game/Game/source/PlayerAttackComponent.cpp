#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"
#include "ActionMove.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData weak1;
    weak1.timing.startTime					= 16.0f;
    weak1.timing.activeDuration				= 5.0f;
    weak1.timing.recoveryDuration			= 9.0f;
    weak1.timing.comboReceiveTime			= 1.0f;
	weak1.timing.isAutoNextAttack			= false;
	weak1.colData.shape						= ShapeType::CAPSULE;
	weak1.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
	weak1.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
	weak1.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
	weak1.colData.radius					= 50.0f;
	weak1.damageData.damage					= 0.1f;
	weak1.damageData.hitStunTime			= 0.0f;
	weak1.damageData.damageInvincibeTime	= 0.0f;
	weak1.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	weak1.knockbackData.knockbackSpeed		= 0.0f;
	weak1.knockbackData.knockbackTime		= 30.0f;
	weak1.effectData.name					= "EF_Attack";
	weak1.soundData.name1					= "SE_SwingAttack";
	weak1.soundData.name2					= "SE_Attack3";
	weak1.cameraShakeData.duration			= 60.0f;
	weak1.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(weak1);

	AttackData weak2;
    weak2.timing.startTime					= 10.0f;
    weak2.timing.activeDuration				= 3.0f;
    weak2.timing.recoveryDuration			= 14.0f;
    weak2.timing.comboReceiveTime			= 1.0f;
	weak2.timing.isAutoNextAttack			= false;
	weak2.colData.shape						= ShapeType::CAPSULE;
	weak2.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak2.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak2.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak2.colData.radius					= 50.0f;
	weak2.damageData.damage					= 0.2f;
	weak2.damageData.hitStunTime			= 0.0f;
	weak2.damageData.damageInvincibeTime	= 0.0f;
	weak2.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	weak2.knockbackData.knockbackSpeed		= 0.0f;
	weak2.knockbackData.knockbackTime		= 30.0f;
	weak2.effectData.name					= "EF_Attack";
	weak2.soundData.name1					= "SE_SwingAttack";
	weak2.soundData.name2					= "SE_Attack2";
	weak2.cameraShakeData.duration			= 60.0f;
	weak2.cameraShakeData.magnitude			= 10.0f;
    AddAttackData(weak2);

    AttackData weak3;
    weak3.timing.startTime					= 4.0f;
    weak3.timing.activeDuration				= 7.0f;
    weak3.timing.recoveryDuration			= 19.0f;
    weak3.timing.comboReceiveTime			= 16.0f;
	weak3.timing.isAutoNextAttack			= true;
	weak3.colData.shape						= ShapeType::CAPSULE;
	weak3.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak3.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak3.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak3.colData.radius					= 50.0f;
	weak3.damageData.damage					= 0.3f;
	weak3.damageData.hitStunTime			= 0.0f;
	weak3.damageData.damageInvincibeTime	= 0.0f;
	weak3.knockbackData.moveDirection		= { 0.0f, 1.0f, 0.0f };
	weak3.knockbackData.knockbackSpeed		= 2.0f;
	weak3.knockbackData.knockbackTime		= 30.0f;
	weak3.effectData.name					= "EF_Attack";
	weak3.soundData.name1					= "SE_SwingAttack";
	weak3.soundData.name2					= "SE_Attack1";
	weak3.cameraShakeData.duration			= 60.0f;
	weak3.cameraShakeData.magnitude			= 10.0f;
    AddAttackData(weak3);

	AttackData weak4;
	weak4.timing.startTime					= 11.0f;
	weak4.timing.activeDuration				= 9.0f;
	weak4.timing.recoveryDuration			= 28.0f;
	weak4.timing.comboReceiveTime			= 1.0f;
	weak4.timing.isAutoNextAttack			= false;
	weak4.colData.shape						= ShapeType::CAPSULE;
	weak4.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak4.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak4.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak4.colData.radius					= 50.0f;
	weak4.damageData.damage					= 0.4f;
	weak4.damageData.hitStunTime			= 0.0f;
	weak4.damageData.damageInvincibeTime	= 0.0f;
	weak4.knockbackData.moveDirection		= { 0.0f, -2.0f, 0.0f };
	weak4.knockbackData.knockbackSpeed		= 2.0f;
	weak4.knockbackData.knockbackTime		= 30.0f;
	weak4.effectData.name					= "EF_Attack";
	weak4.soundData.name1					= "SE_SwingAttack";
	weak4.soundData.name2					= "SE_Attack2";
	weak4.cameraShakeData.duration			= 60.0f;
	weak4.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(weak4);

	AttackData weak5;
	weak5.timing.startTime					= 30.0f;
	weak5.timing.activeDuration				= 25.0f;
	weak5.timing.recoveryDuration			= 0.0f;
	weak5.timing.comboReceiveTime			= 0.0f;
	weak5.timing.isAutoNextAttack			= false;
	weak5.colData.shape						= ShapeType::CAPSULE;   
	weak5.colData.size						= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak5.colData.topOffset					= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak5.colData.bottomOffset				= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak5.colData.radius					= 50.0f;
	weak5.damageData.damage					= 0.5f;
	weak5.damageData.hitStunTime			= 0.0f;
	weak5.damageData.damageInvincibeTime	= 0.0f;
	weak5.knockbackData.moveDirection		= { 0.0f, 0.0f, 0.0f };
	weak5.knockbackData.knockbackSpeed		= 2.0f;
	weak5.knockbackData.knockbackTime		= 30.0f;
	weak5.effectData.name					= "EF_Attack";
	weak5.soundData.name1					= "SE_SwingAttack";
	weak5.soundData.name2					= "SE_Attack3";
	weak5.cameraShakeData.duration			= 60.0f;
	weak5.cameraShakeData.magnitude			= 10.0f;
	AddAttackData(weak5);
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