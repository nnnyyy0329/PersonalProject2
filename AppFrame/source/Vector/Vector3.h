/*****************************************
* file   Vector3D.h
* brief  3次元ベクトルクラス
* author 成田 悠真
* date   2026/1/22
******************************************/

#pragma once

namespace Vec3
{
	/// @brief 3次元ベクトルクラス
	class Vector3
	{
	public:

		Vector3();
		Vector3(float x, float y, float z);

		Vector3(const Vector3&) = default;
		Vector3(Vector3&&) = default;
		~Vector3() = default;
		
		//===========================================================================
		// 演算子オーバーロード
		//===========================================================================

		/// @brief コピー代入演算子
		///
		/// @param v 代入するベクトル
		/// 
		/// @return 代入後のベクトル
		Vector3& operator=(const Vector3&) = default;

		/// @brief ムーブ代入演算子
		///
		/// @param v 代入するベクトル
		/// 
		/// @return 代入後のベクトル
		Vector3& operator=(Vector3&&) = default;

		/// @brief 加算演算子
		///
		/// @param v 加算するベクトル
		/// 
		/// @return 加算結果のベクトル
		Vector3 operator+(const Vector3& v) const;

		/// @brief 減算演算子
		///
		/// @param v 減算するベクトル
		/// 
		/// @return 減算結果のベクトル
		Vector3 operator-(const Vector3 & v) const;

		/// @brief 乗算演算子
		///
		/// @param v 乗算するスカラー値
		/// 
		/// @return 乗算結果のベクトル
		Vector3 operator*(float v) const;

		/// @brief 除算演算子
		///
		/// @param v 除算するスカラー値
		/// 
		/// @return 除算結果のベクトル
		Vector3 operator/(float v) const;

		/// @brief 加算代入演算子
		///
		/// @param v 加算するベクトル
		/// 
		/// @return 加算後のベクトル
		Vector3& operator+=(const Vector3& v);

		/// @brief 減算代入演算子
		///
		/// @param v 減算するベクトル
		/// 
		/// @return 減算後のベクトル
		Vector3& operator-=(const Vector3& v);

		/// @brief 乗算代入演算子
		///
		/// @param v 乗算するスカラー値
		/// 
		/// @return 乗算後のベクトル
		Vector3& operator*=(float v);

		/// @brief 除算代入演算子
		///
		/// @param v 除算するスカラー値
		/// 
		/// @return 除算後のベクトル
		Vector3& operator/=(float v);

		//===========================================================================
		// ゲッター
		//===========================================================================

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetZ() const { return m_z; }
		Vector3 Get()const { return Vector3(m_x, m_y, m_z); }

		//===========================================================================
		// セッター
		//===========================================================================

		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }
		void SetZ(float z) { m_z = z; }
		void Set(float x, float y, float z);
		void Set(const Vector3& v);

		//===========================================================================
		// 内部関数
		//===========================================================================

		/// @brief 2つのベクトルの加算を行う関数
		///
		/// @param otherV 加算するベクトル
		/// 
		/// @return 加算結果のベクトル
		Vector3 Add(const Vector3& otherV);

		/// @brief 2つのベクトルの減算を行う関数
		///
		/// @param otherV 減算するベクトル
		/// 
		/// @return 減算結果のベクトル
		Vector3 Sub(const Vector3& otherV);

		/// @brief ベクトルを正規化する関数
		/// 
		/// @return 正規化されたベクトル
		Vector3 Normalize() const;

		/// @brief 2つのベクトルの内積を計算する関数
		/// 
		/// @param v 内積を計算するベクトル
		/// 
		/// @return 内積の値
		float Dot(const Vector3& otherV) const;

		/// @brief ベクトルの長さを計算する関数
		/// 
		/// @return ベクトルの長さ
		float Length() const;

	private:

		float m_x = 0.0f;
		float m_y = 0.0f;
		float m_z = 0.0f;

	};
};
