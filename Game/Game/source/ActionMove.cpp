#include "ActionMove.h"
#include "Character.h"
#include "MoveComponent.h"

void ActionMove::Execute(Character& character)
{
	// キャラクターの移動コンポーネントを取得
	auto moveComponent = character.GetComponent<MoveComponent<Character>>();
	if(!moveComponent) { return; }

	// コンポーネントから移動ベクトルを取得
	VECTOR moveVector = moveComponent->GetMoveVector();

	// 移動ベクトルの大きさが0より大きい場合
	if(VSize(moveVector) > 0.0f)
	{
		// キャラクターのオブジェクトデータを取得
		ObjectData data = character.GetObjectData();

		// 移動ベクトルをキャラクターの位置に加算
		data.pos = VAdd(data.pos, moveVector);

		// 更新されたオブジェクトデータをキャラクターに設定
		character.SetObjectData(data);
	}
	else
	{

	}
}