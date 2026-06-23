#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"
#include "ActionMove.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData weak1;
    weak1.startTime = 16.0f;
    weak1.activeDuration = 7.0f;
    weak1.recoveryDuration = 7.0f;
    weak1.comboReceiveTime = 1.0f;
	weak1.colData.shape = ShapeType::CAPSULE;
	weak1.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak1.colData.offset = VGet(0.0f, 0.0f, 50.0f);
	weak1.colData.radius = 100.0f;
    AddAttackData(weak1);

	AttackData weak2;
    weak2.startTime = 10.0f;
    weak2.activeDuration = 3.0f;
    weak2.recoveryDuration = 18.0f;
    weak2.comboReceiveTime = 1.0f;
	weak2.colData.shape = ShapeType::CAPSULE;
	weak2.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak2.colData.offset = VGet(100.0f, 0.0f, 0.0f);
    weak2.colData.radius = 100.0f;
    AddAttackData(weak2);

    AttackData weak3;
    weak3.startTime = 4.0f;
    weak3.activeDuration = 7.0f;
    weak3.recoveryDuration = 19.0f;
    weak3.comboReceiveTime = 1.0f;
	weak3.colData.shape = ShapeType::CAPSULE;
	weak3.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak3.colData.offset = VGet(0.0f, 100.0f, 0.0f);
    weak3.colData.radius = 100.0f;
    AddAttackData(weak3);

	AttackData weak4;
	weak4.startTime = 11.0f;
	weak4.activeDuration = 9.0f;
	weak4.recoveryDuration = 30.0f;
	weak4.comboReceiveTime = 1.0f;
	weak4.colData.shape = ShapeType::CAPSULE;
	weak4.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak4.colData.offset = VGet(0.0f, 0.0f, -100.0f);
	weak4.colData.radius = 100.0f;
	AddAttackData(weak4);

	AttackData weak5;
	weak5.startTime = 30.0f;
	weak5.activeDuration = 30.0f;
	weak5.recoveryDuration = 0.0f;
	weak5.comboReceiveTime = 0.0f;
	weak5.colData.shape = ShapeType::CAPSULE;   
	weak5.colData.size = VGet(1.0f, 1.0f, 1.0f);
	weak5.colData.offset = VGet(100.0f, 100.0f, 0.0f);
	weak5.colData.radius = 100.0f;
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
        if(!owner.IsCurrentAction<ActionAttack>())
        {
            if(m_comboIndex < m_attackDataList.size())
            {
				owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[m_comboIndex]));
				m_comboIndex++;

                printfDx("攻撃入力が処理されました\n");
            }
        }
        else
        {
            auto* currentAction = owner.GetCurrentAction<ActionAttack>();
            if(currentAction && currentAction->IsCancelable())
            {
                if(m_comboIndex < m_attackDataList.size())
                {
					owner.SetAction(std::make_unique<ActionAttack>(m_attackDataList[m_comboIndex]));
					m_comboIndex++;

                    printfDx("コンボ攻撃入力が処理されました\n");
                }
            }
        }
    }
}