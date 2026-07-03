#include "PlayerMoveCommand.h"
#include "Character.h"
#include "InputManager.h"
#include "ActionMove.h"

void PlayerMoveCommand::Execute(Character& owner)
{
	// 入力状態を取得
	auto& pad = InputManager::GetInstance().GetPad(0);
	if(!pad.IsConnected()) { return; }

	// 左スティックの入力がある場合、移動アクションを設定する
	if(pad.GetLeftStickX() != 0.0f || pad.GetLeftStickY() != 0.0f)
	{
		// 移動アクションを設定する
		owner.SetAction(std::make_unique<ActionMove>());
	}
}