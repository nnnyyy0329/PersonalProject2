#include "PlayerAttackCommand.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionAttack.h"
#include "PlayerAttackComponent.h"

void PlayerAttackCommand::Execute(Character& owner)
{
	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);
	if(!pad_1.IsConnected()) { return; }

	// Aボタンが押された場合
	if(pad_1.isTrigger(PadButton::A))
	{
		// プレイヤーの攻撃コンポーネントを取得
		auto playerAttackComp = owner.GetComponent<PlayerAttackComponent>();
		if(!playerAttackComp) { return; }

		// 攻撃処理をする
		playerAttackComp->TryAttack(owner);
	}
}