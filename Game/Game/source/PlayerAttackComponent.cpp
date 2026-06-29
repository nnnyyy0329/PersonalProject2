#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"
#include "ActionMove.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData weak1;
    weak1.timing.startTime = 16.0f;
    weak1.timing.activeDuration = 7.0f;
    weak1.timing.recoveryDuration = 7.0f;
    weak1.timing.comboReceiveTime = 1.0f;
	weak1.colData.shape = ShapeType::CAPSULE;
	weak1.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak1.colData.topOffset = VGet(0.0f, 100.0f, -80.0f);
	weak1.colData.bottomOffset = VGet(0.0f, 0.0f, -80.0f);
	weak1.colData.radius = 50.0f;
	weak1.effectData.name = "EF_Attack";
    AddAttackData(weak1);

	AttackData weak2;
    weak2.timing.startTime = 10.0f;
    weak2.timing.activeDuration = 3.0f;
    weak2.timing.recoveryDuration = 18.0f;
    weak2.timing.comboReceiveTime = 1.0f;
	weak2.colData.shape = ShapeType::CAPSULE;
	weak2.colData.size = VGet(1.0f, 1.0f, 1.0f);
    weak2.colData.topOffset = VGet(0.0f, 100.0f, -80.0f);
    weak2.colData.bottomOffset = VGet(0.0f, 0.0f, -80.0f);
    weak2.colData.radius = 50.0f;
	weak2.effectData.name = "EF_Attack";
    AddAttackData(weak2);

    AttackData weak3;
    weak3.timing.startTime = 4.0f;
    weak3.timing.activeDuration = 7.0f;
    weak3.timing.recoveryDuration = 19.0f;
    weak3.timing.comboReceiveTime = 1.0f;
	weak3.colData.shape = ShapeType::CAPSULE;
	weak3.colData.size = VGet(1.0f, 1.0f, 1.0f);
    weak3.colData.topOffset = VGet(0.0f, 100.0f, -80.0f);
    weak3.colData.bottomOffset = VGet(0.0f, 0.0f, -80.0f);
    weak3.colData.radius = 50.0f;
	weak3.effectData.name = "EF_Attack";
    AddAttackData(weak3);

	AttackData weak4;
	weak4.timing.startTime = 11.0f;
	weak4.timing.activeDuration = 9.0f;
	weak4.timing.recoveryDuration = 30.0f;
	weak4.timing.comboReceiveTime = 1.0f;
	weak4.colData.shape = ShapeType::CAPSULE;
	weak4.colData.size = VGet(1.0f, 1.0f, 1.0f);
    weak4.colData.topOffset = VGet(0.0f, 100.0f, -80.0f);
    weak4.colData.bottomOffset = VGet(0.0f, 0.0f, -80.0f);
    weak4.colData.radius = 50.0f;
	weak4.effectData.name = "EF_Attack";
	AddAttackData(weak4);

	AttackData weak5;
	weak5.timing.startTime = 30.0f;
	weak5.timing.activeDuration = 30.0f;
	weak5.timing.recoveryDuration = 0.0f;
	weak5.timing.comboReceiveTime = 0.0f;
	weak5.colData.shape = ShapeType::CAPSULE;   
	weak5.colData.size = VGet(1.0f, 1.0f, 1.0f);
    weak5.colData.topOffset = VGet(0.0f, 100.0f, -80.0f);
    weak5.colData.bottomOffset = VGet(0.0f, 0.0f, -80.0f);
    weak5.colData.radius = 50.0f;
	weak5.effectData.name = "EF_Attack";
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

	// 攻撃入力を処理する
	InputAttack(owner);
}

void PlayerAttackComponent::InputAttack(Character& owner)
{
    // 1Pのパッド情報取得
    const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return; }

	// Aボタンが押された場合
    if(pad_1.isTrigger(PadButton::A))
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
            }
        }
		// 現在のアクションが攻撃アクションである場合
        else
        {
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
                }
            }
        }
    }
}