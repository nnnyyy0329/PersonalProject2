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
		~Vector3();
		
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

		float GetX() const;
		float GetY() const;
		float GetZ() const;
		Vector3 Get()const { return Vector3(m_x, m_y, m_z); }

		//===========================================================================
		// セッター
		//===========================================================================

		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }
		void SetZ(float z) { m_z = z; }
		void Set(const Vector3& v);

		//===========================================================================
		// 内部関数
		//===========================================================================

		/// @brief 2つのベクトルの加算を行う関数
		///
		/// @param v1 1つ目のベクトル
		/// @param v2 2つ目のベクトル
		/// 
		/// @return 加算結果のベクトル
		Vector3 Add(const Vector3& v1, const Vector3& v2);

		/// @brief 2つのベクトルの減算を行う関数
		///
		/// @param v1 1つ目のベクトル
		/// @param v2 2つ目のベクトル
		/// 
		/// @return 減算結果のベクトル
		Vector3 Sub(const Vector3& v1, const Vector3& v2);

		/// @brief ベクトルを正規化する関数
		///
		/// @param v 正規化するベクトル
		/// 
		/// @return 正規化されたベクトル
		Vector3 Norm(const Vector3& v);

		/// @brief 2つのベクトルの内積を計算する関数
		///
		/// @param v1 内積を計算するベクトル1
		/// @param v2 内積を計算するベクトル2
		/// 
		/// @return 内積の値
		float Dot(const Vector3& v1, const Vector3& v2);

		/// @brief ベクトルの長さを計算する関数
		///
		/// @param v 長さを計算するベクトル
		/// 
		/// @return ベクトルの長さ
		float Length(const Vector3& v);

	private:

		float m_x = 0.0f;
		float m_y = 0.0f;
		float m_z = 0.0f;

	};
};
