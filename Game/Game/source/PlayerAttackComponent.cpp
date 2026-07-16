#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"
#include "ActionMove.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData weak1;
    weak1.timing.startTime			= 16.0f;
    weak1.timing.activeDuration		= 7.0f;
    weak1.timing.recoveryDuration	= 7.0f;
    weak1.timing.comboReceiveTime	= 1.0f;
	weak1.colData.shape				= ShapeType::CAPSULE;
	weak1.colData.size				= Vec3::Vector3(1.0f, 1.0f, 1.0f);
	weak1.colData.topOffset			= Vec3::Vector3(0.0f, 100.0f, -80.0f);
	weak1.colData.bottomOffset		= Vec3::Vector3(0.0f, 0.0f, -80.0f);
	weak1.colData.radius			= 50.0f;
	weak1.effectData.name			= "EF_Attack";
	weak1.cameraShakeData.duration	= 60.0f;
	weak1.cameraShakeData.magnitude = 10.0f;
	AddAttackData(weak1);

	AttackData weak2;
    weak2.timing.startTime			= 10.0f;
    weak2.timing.activeDuration		= 3.0f;
    weak2.timing.recoveryDuration	= 18.0f;
    weak2.timing.comboReceiveTime	= 1.0f;
	weak2.colData.shape				= ShapeType::CAPSULE;
	weak2.colData.size				= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak2.colData.topOffset			= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak2.colData.bottomOffset		= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak2.colData.radius			= 50.0f;
	weak2.effectData.name			= "EF_Attack";
	weak2.cameraShakeData.duration	= 60.0f;
	weak2.cameraShakeData.magnitude = 10.0f;
    AddAttackData(weak2);

    AttackData weak3;
    weak3.timing.startTime			= 4.0f;
    weak3.timing.activeDuration		= 7.0f;
    weak3.timing.recoveryDuration	= 19.0f;
    weak3.timing.comboReceiveTime	= 1.0f;
	weak3.colData.shape				= ShapeType::CAPSULE;
	weak3.colData.size				= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak3.colData.topOffset			= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak3.colData.bottomOffset		= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak3.colData.radius			= 50.0f;
	weak3.effectData.name			= "EF_Attack";
	weak3.cameraShakeData.duration	= 60.0f;
	weak3.cameraShakeData.magnitude = 10.0f;
    AddAttackData(weak3);

	AttackData weak4;
	weak4.timing.startTime			= 11.0f;
	weak4.timing.activeDuration		= 9.0f;
	weak4.timing.recoveryDuration	= 30.0f;
	weak4.timing.comboReceiveTime	= 1.0f;
	weak4.colData.shape				= ShapeType::CAPSULE;
	weak4.colData.size				= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak4.colData.topOffset			= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak4.colData.bottomOffset		= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak4.colData.radius			= 50.0f;
	weak4.effectData.name			= "EF_Attack";
	weak4.cameraShakeData.duration	= 60.0f;
	weak4.cameraShakeData.magnitude = 10.0f;
	AddAttackData(weak4);

	AttackData weak5;
	weak5.timing.startTime			= 30.0f;
	weak5.timing.activeDuration		= 30.0f;
	weak5.timing.recoveryDuration	= 0.0f;
	weak5.timing.comboReceiveTime	= 0.0f;
	weak5.colData.shape				= ShapeType::CAPSULE;   
	weak5.colData.size				= Vec3::Vector3(1.0f, 1.0f, 1.0f);
    weak5.colData.topOffset			= Vec3::Vector3(0.0f, 100.0f, -80.0f);
    weak5.colData.bottomOffset		= Vec3::Vector3(0.0f, 0.0f, -80.0f);
    weak5.colData.radius			= 50.0f;
	weak5.effectData.name			= "EF_Attack";
	weak5.cameraShakeData.duration	= 60.0f;
	weak5.cameraShakeData.magnitude = 10.0f;
	AddAttackData(weak5);
}

void PlayerAttackComponent::Update(Character& owner)
{
	// 現在のアクションが攻撃アクションでない場合
    if(!owner.IsCurrentAction<ActionAttack>())
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
		// コンボ攻撃が攻撃のデータ数より少ない場合
		if(m_comboIndex < m_attackDataList.size())
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
		// コンボ攻撃が攻撃のデータ数より少ない場合
		if(m_comboIndex < m_attackDataList.size())
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