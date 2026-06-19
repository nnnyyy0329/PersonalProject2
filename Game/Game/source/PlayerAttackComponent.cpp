#include "PlayerAttackComponent.h"
#include "Character.h"
#include "InputManager.h"
#include "AttackAction.h"
#include "ActionMove.h"

PlayerAttackComponent::PlayerAttackComponent()
{
    AttackData weak1;
    weak1.startTime = 10.0f;
    weak1.activeDuration = 20.0f;
    weak1.recoveryDuration = 20.0f;
    weak1.comboReceiveTime = 15.0f;
    AddAttackData(weak1);

	AttackData weak2;
    weak2.startTime = 10.0f;
    weak2.activeDuration = 20.0f;
    weak2.recoveryDuration = 20.0f;
    weak2.comboReceiveTime = 15.0f;
    AddAttackData(weak2);

    AttackData weak3;
    weak3.startTime = 10.0f;
    weak3.activeDuration = 20.0f;
    weak3.recoveryDuration = 20.0f;
    weak3.comboReceiveTime = 15.0f;
    AddAttackData(weak3);
}

void PlayerAttackComponent::Update(Character& owner)
{
	// 現在のアクションが攻撃アクションでない場合
    if(!owner.IsCurrentAction<AttackAction>())
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
        if(!owner.IsCurrentAction<AttackAction>())
        {
            if(m_comboIndex < m_attackDataList.size())
            {
				owner.SetAction(std::make_unique<AttackAction>(m_attackDataList[m_comboIndex]));
				m_comboIndex++;

                printfDx("攻撃入力が処理されました\n");
            }
        }
        else
        {
            auto* currentAction = owner.GetCurrentAction<AttackAction>();
            if(currentAction && currentAction->IsCancelable())
            {
                if(m_comboIndex < m_attackDataList.size())
                {
					owner.SetAction(std::make_unique<AttackAction>(m_attackDataList[m_comboIndex]));
					m_comboIndex++;

                    printfDx("コンボ攻撃入力が処理されました\n");
                }
            }
        }
    }
}