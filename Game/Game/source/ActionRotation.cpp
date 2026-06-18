#include "ActionRotation.h"
#include "Character.h"
#include "RotationComponent.h"
#include <cmath>

namespace
{
	constexpr float ROTATION_SPEED = 0.15f;	// 回転の速度
}

void ActionRotation::Execute(Character& character)
{
	// キャラクターの回転コンポーネントを取得
	auto rotationComponent = character.GetComponent<RotationComponent<Character>>();
	if(!rotationComponent) { return; }

	// コンポーネントから回転ベクトルを取得
	VECTOR rotVector = rotationComponent->GetRotVector();

	// 回転ベクトルの大きさがほぼ0.0の場合はスキップ
	if(VSize(rotVector) < 0.0001f) { return; }



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
	while(diff > DX_PI_F)  { diff -= DX_PI_F * 2.0f; }
	while(diff < -DX_PI_F) { diff += DX_PI_F * 2.0f; }

	// 回転速度を掛けて、現在の角度を更新
	currentAngle += diff * ROTATION_SPEED;
	data.rot.y = currentAngle;

	// 更新されたオブジェクトデータをキャラクターに設定
	character.SetObjectData(data);
}