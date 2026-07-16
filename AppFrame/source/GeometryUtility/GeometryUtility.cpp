#include "GeometryUtility.h"

namespace GeometryUtility
{
	bool IsFacing(const Vec3::Vector3& fromPos, const Vec3::Vector3& fromDir, const Vec3::Vector3& targetPos, float dotThreshold)
	{
		// 判定対象へのベクトルを計算
		Vec3::Vector3 toTarget = targetPos - fromPos;
		toTarget.SetY(0.0f);	// Y軸を無視

		// ベクトルの長さがほぼ0の場合は判定不可
		if(toTarget.Length() < 0.001f) return false;
		toTarget.Normalize();	// 正規化

		// 判定元の前方向ベクトルを正規化
		Vec3::Vector3 forwardDir = fromDir;
		forwardDir.SetY(0.0f);
		forwardDir.Normalize();
		
		// 判定対象へのベクトルと前方向ベクトルの内積を計算
		float dot = forwardDir.Dot(toTarget);

		// 内積が閾値以上なら前方にあると判定
		return dot > dotThreshold;
	}

	Vec3::Vector3 ConvertLocalToWorld(const Vec3::Vector3& localDir, const Vec3::Vector3& forwardDir)
	{
		// 前方向ベクトルを正規化
		Vec3::Vector3 forward = forwardDir.Normalize();

		// 上方向ベクトル
		Vec3::Vector3 up = { 0.0f, 1.0f, 0.0f };

		// 右方向ベクトルを上方向ベクトルと前方向ベクトルの外積を正規化して計算
		Vec3::Vector3 right = up.Cross(forward).Normalize();

		// 上方向ベクトルを前方向ベクトルと右方向ベクトルの外積を正規化して計算
		up = forward.Cross(right).Normalize();

		// ローカル座標をワールド座標に変換
		return (right * localDir.GetX()) + (up * localDir.GetY()) + (forward * localDir.GetZ());
	}
}
