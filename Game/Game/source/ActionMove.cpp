#include "ActionMove.h"
#include "Character.h"
#include "InputManager.h"

void ActionMove::Execute(Character& character)
{
	// プレイヤーの移動処理を実行
	PlayerMove(character);
}

void ActionMove::PlayerMove(Character& character)
{
	//// 1Pのパッド情報取得
	//const auto& pad_1 = InputManager::GetInstance().GetPad(0);

	//if(pad_1.IsConnected())
	//{
	//	ObjectData data = character.GetObjectData();
	//	data.pos = VAdd(data.pos, VGet(1.0f, 0.0f, 0.0f));
	//	character.SetObjectData(data);
	//}


	// 1Pのパッド情報取得
	const auto& pad_1 = InputManager::GetInstance().GetPad(0);

	if(pad_1.IsConnected())
	{
		float moveX = static_cast<float>(pad_1.GetLeftStickX());
		float moveZ = static_cast<float>(pad_1.GetLeftStickY());
		VECTOR moveVector = VGet(moveX, 0.0f, moveZ);

		if(VSize(moveVector) > 0.0f)
		{
			ObjectData data = character.GetObjectData();
			data.pos = VAdd(data.pos, moveVector);
			character.SetObjectData(data);
		}
	}
}