#include "CameraShake.h"
#include "DxLib.h"

namespace
{
	// ランダム値の最大値
	constexpr int MAX_RAND = 2000;

	// ランダム値の半分の値
	constexpr int HALF_MAX_RAND = MAX_RAND / 2;

	// ランダム値のスケール
	constexpr float RANDOM_SCALE = 1000.0f;
}

void CameraShake::Update()
{
	// タイマーが動いていなければ何もしない
	if(m_shakeTimer <= 0.0f)
	{
		// 振動オフセットをリセット
		m_shakeOffset = Vec3::Vector3(0.0f, 0.0f, 0.0f);

		return;
	}

	// タイマーを減らす
	m_shakeTimer -= 1.0f;

	// 時間切れになったら即終了
	if(m_shakeTimer <= 0.0f)
	{
		// 振動オフセットをリセット
		m_shakeOffset = {0.0f, 0.0f, 0.0f};

		return;
	}

	// 残り時間の割合
	float rate = m_shakeTimer / m_duration;

	// 振動の強さを計算
	float currentMagnitude = m_magnitude * rate;

	// ランダムな振動オフセットを計算
	float randX = ((GetRand(MAX_RAND) - HALF_MAX_RAND) / RANDOM_SCALE) * currentMagnitude;
	float randY = ((GetRand(MAX_RAND) - HALF_MAX_RAND) / RANDOM_SCALE) * currentMagnitude;
	float randZ = ((GetRand(MAX_RAND) - HALF_MAX_RAND) / RANDOM_SCALE) * currentMagnitude;

	// 振動オフセットを更新
	m_shakeOffset = Vec3::Vector3(randX, randY, randZ);
}

void CameraShake::PlayShake(float duration, float magnitude)
{
	m_shakeTimer	= duration;
	m_duration		= duration;
	m_magnitude		= magnitude;
	m_shakeOffset	= Vec3::Vector3(0.0f, 0.0f, 0.0f);
}
