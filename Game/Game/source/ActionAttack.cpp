#include "ActionAttack.h"
#include "Character.h"
#include "CollisionComponent.h"

void ActionAttack::Update(Character& character)
{
	// 攻撃が開始されていない場合
	if(m_currentPhase == AttackPhase::NONE)
	{
		// 攻撃開始フェーズに移行する
		NonePhaseProcess();
		return;
	}

	// コンボ受付時間かを更新する
	UpdateComboReceive();

	// 現在のフェーズの経過時間を更新する
	m_stateTime += 1.0f;

	// 攻撃のフェーズを更新する
	UpdateAttackPhase(character);

	// コリジョンの有効化を行う
	EnableCollision(character);
}

void ActionAttack::NonePhaseProcess()
{
	// 攻撃開始フェーズに移行する
	m_currentPhase = AttackPhase::STARTUP;
	m_stateTime = 0.0f;
	m_isCancelable = false;
}

void ActionAttack::UpdateComboReceive()
{
	// 攻撃有効フェーズで、かつ攻撃有効時間内であれば
	if((m_currentPhase == AttackPhase::RECOVERY) && (m_stateTime < m_attackData.timing.recoveryDuration))
	{
		// 攻撃がコンボを受付中かどうかを更新する
		if(m_stateTime >= m_attackData.timing.comboReceiveTime)
		{
			m_isCancelable = true;
		}
	}
}

void ActionAttack::UpdateAttackPhase(Character& character)
{
	// 攻撃のフェーズを更新する
	switch(m_currentPhase)
	{
		case AttackPhase::STARTUP:	// 攻撃開始フェーズ
		{
			// 攻撃開始時間を過ぎたら攻撃有効フェーズに移行する
			if(m_stateTime >= m_attackData.timing.startTime)
			{
				m_currentPhase = AttackPhase::ACTIVE;
				m_stateTime = 0.0f;



				// 攻撃が開始されたときの処理を行う（仮実装）
				OnAttackActive(m_attackData, character);



				printf("攻撃が開始されました\n");
			}

			break;
		}

		case AttackPhase::ACTIVE:	// 攻撃有効フェーズ
		{
			// 攻撃有効時間を過ぎたら攻撃後の硬直フェーズに移行する
			if(m_stateTime >= m_attackData.timing.activeDuration)
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
			if(m_stateTime >= m_attackData.timing.recoveryDuration)
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

void ActionAttack::EnableCollision(Character& character)
{
	// コリジョンコンポーネントを取得する
	auto colComponent = character.GetComponent<CollisionComponent<Character>>();
	if(!colComponent) { return; }

	// 攻撃有効フェーズで、かつ攻撃有効時間内であれば
	if(m_currentPhase == AttackPhase::ACTIVE && m_stateTime < m_attackData.timing.activeDuration)
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





#include "Server/ResourceServer.h"
#include "Server/SoundServer.h"
#include "Server/EffectServer.h"
#include "VectorConverter/VectorConverter.h"

void ActionAttack::OnAttackActive(const AttackData& attackData, Character& character)
{
	auto rs = ResourceServer::GetInstance();
	auto ss = SoundServer::GetInstance();
	auto es = EffectServer::GetInstance();

	int seHandle = ss->Play(attackData.soundData.name, DX_PLAYTYPE_BACK);
	es->Play(attackData.effectData.name, Vec::ToDxVec(character.GetObjectData().pos));
	es->Play("EF_Damage1", Vec::ToDxVec(character.GetObjectData().pos));
	es->Play("EF_Damage2", Vec::ToDxVec(character.GetObjectData().pos));
}