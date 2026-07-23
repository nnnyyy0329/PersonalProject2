#include "ActionMove.h"
#include "Character.h"
#include "MoveComponent.h"
#include "RotationComponent.h"
#include "Vector/Vector3.h"

namespace
{
	// 円周率
	constexpr float PI = 3.1415926535f;

	// 2π
	constexpr float TWO_PI = PI * 2.0f;

	// 回転の速度
	constexpr float ROTATION_SPEED = 0.15f;

	// 反対方向に回転するための角度
	constexpr float OPPOSITE_ANGLE = PI * 2.0f;
}

void ActionMove::Update(Character& character)
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
		Vec3::Vector3 moveVector = moveComponent->GetMoveVector();

		// 移動ベクトルの大きさが0より大きい場合
		if(moveVector.Length() > 0.0f)
		{
			// キャラクターのオブジェクトデータを取得
			ObjectData data = character.GetObjectData();

			// 移動ベクトルをキャラクターの位置に加算
			data.pos = data.pos + moveVector;

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
		Vec3::Vector3 rotVector = rotationComponent->GetRotVector();
		if(rotVector.Length() <= 0.0f) { return; }

		// 回転ベクトルから角度を計算
		float targetAngle = atan2f(rotVector.GetX(), rotVector.GetZ());

		// モデルの正面がZ軸のマイナス方向の場合180度加算する
		targetAngle += PI;

		// キャラクターの現在の回転角度を取得
		ObjectData data = character.GetObjectData();
		float currentAngle = data.rot.GetY();



		//printfDx("rotVec = %.2f %.2f  target = %.2f  current = %.2f\n",rotVector.GetX(), rotVector.GetZ(),targetAngle,currentAngle);

		

		// 角度の差を計算
		float diff = targetAngle - currentAngle;

		// 角度の差が180度を超える場合は、反対方向に回転する
		while(diff > PI)  { diff -= OPPOSITE_ANGLE; }
		while(diff < -PI) { diff += OPPOSITE_ANGLE; }

		// 回転速度を掛けて、現在の角度を更新
		currentAngle += diff * ROTATION_SPEED;



		while(currentAngle >= TWO_PI){ currentAngle -= TWO_PI; }
		while(currentAngle < 0.0f){ currentAngle += TWO_PI; }



		data.rot.SetY(currentAngle);

		// 更新されたオブジェクトデータをキャラクターに設定
		character.SetObjectData(data);
	}
}