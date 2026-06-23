#include "AttackAction.h"
#include "Character.h"
#include "CollisionComponent.h"

void AttackAction::Execute(Character& character)
{
	// 攻撃が開始されていない場合
	if(m_currentPhase == AttackPhase::NONE)
	{
		// 攻撃開始フェーズに移行する
		NonePhaseProcess();

		return;
	}

	// 現在のフェーズの経過時間を更新する
	m_stateTime += 1.0f;

	// 攻撃がコンボを受付中かどうかを更新する
	if(m_stateTime >= m_attackData.comboReceiveTime)
	{
		m_isCancelable = true;
	}

	// 攻撃のフェーズを更新する
	UpdateAttackPhase(character);

	// コリジョンの有効化を行う
	EnableCollision(character);
}

void AttackAction::NonePhaseProcess()
{
	// 攻撃開始フェーズに移行する
	m_currentPhase = AttackPhase::STARTUP;
	m_stateTime = 0.0f;
	m_isCancelable = false;
}

void AttackAction::UpdateAttackPhase(Character& character)
{
	// 攻撃のフェーズを更新する
	switch(m_currentPhase)
	{
		case AttackPhase::STARTUP:	// 攻撃開始フェーズ
		{
			// 攻撃開始時間を過ぎたら攻撃有効フェーズに移行する
			if(m_stateTime >= m_attackData.startTime)
			{
				m_currentPhase = AttackPhase::ACTIVE;
				m_stateTime = 0.0f;

				printfDx("攻撃が開始されました\n");
			}

			break;
		}

		case AttackPhase::ACTIVE:	// 攻撃有効フェーズ
		{
			// 攻撃有効時間を過ぎたら攻撃後の硬直フェーズに移行する
			if(m_stateTime >= m_attackData.activeDuration)
			{
				m_currentPhase = AttackPhase::RECOVERY;
				m_stateTime = 0.0f;

				printf("攻撃が有効になりました\n");
			}

			break;
		}

		case AttackPhase::RECOVERY:	// 攻撃後の硬直フェーズ
		{
			// 攻撃後の硬直時間を過ぎたら攻撃が無効になる
			if(m_stateTime >= m_attackData.recoveryDuration)
			{
				m_currentPhase = AttackPhase::NONE;
				m_stateTime = 0.0f;
				m_isFinished = true;

				printf("攻撃が無効になりました\n");
			}

			break;
		}

		default:
		{
			break;
		}
	}
}

void AttackAction::EnableCollision(Character& character)
{
	// コリジョンコンポーネントを取得する
	auto colComponent = character.GetComponent<CollisionComponent<Character>>();
	if(!colComponent) { return; }

	// 攻撃有効フェーズで、かつ攻撃有効時間内であれば
	if(m_currentPhase == AttackPhase::ACTIVE && m_stateTime < m_attackData.activeDuration)
	{
		// コリジョンを有効にする
		colComponent->ActiveCollision(m_attackData.colData);

		//printfDx("コリジョンが有効になりました\n");
	}
	// 攻撃有効フェーズでない場合、または攻撃有効時間を過ぎている場合
	else
	{
		// コリジョンを無効にする
		colComponent->DeactiveCollision();
	}
}