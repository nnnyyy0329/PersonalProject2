#include "ActionMove.h"
#include "Character.h"
#include "MoveComponent.h"
#include "RotationComponent.h"

namespace
{
	// 回転の速度
	constexpr float ROTATION_SPEED = 0.15f;

	// 反対方向に回転するための角度
	constexpr float OPPOSITE_ANGLE = DX_PI_F * 2.0f;
}

void ActionMove::Execute(Character& character)
{
	// キャラクターを移動させる
	Move(character);

	// キャラクターを回転させる
	Rotate(character);
}

void ActionMove::Move(Character& character)
{
	// キャラクターの移動コンポーネントを取得
	auto moveComponent = character.GetComponent<MoveComponent<Character>>();
	if(moveComponent)
	{
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
	}
}

void ActionMove::Rotate(Character& character)
{
	// キャラクターの回転コンポーネントを取得
	auto rotationComponent = character.GetComponent<RotationComponent<Character>>();
	if(rotationComponent)
	{
		// コンポーネントから回転ベクトルを取得
		VECTOR rotVector = rotationComponent->GetRotVector();
		if(VSize(rotVector) <= 0.0f) { return; }

		// 回転ベクトルから角度を計算
		float targetAngle = atan2f(rotVector.x, rotVector.z);

		// モデルの正面がZ軸のマイナス方向の場合180度加算する
		targetAngle += DX_PI_F;

		// キャラクターの現在の回転角度を取得
		ObjectData data = character.GetObjectData();
		float currentAngle = data.rot.y;

		// 角度の差を計算
		float diff = targetAngle - currentAngle;

		// 角度の差が180度を超える場合は、反対方向に回転する
		while(diff > DX_PI_F) { diff -= OPPOSITE_ANGLE; }
		while(diff < -DX_PI_F) { diff += OPPOSITE_ANGLE; }

		// 回転速度を掛けて、現在の角度を更新
		currentAngle += diff * ROTATION_SPEED;
		data.rot.y = currentAngle;

		// 更新されたオブジェクトデータをキャラクターに設定
		character.SetObjectData(data);
	}
}