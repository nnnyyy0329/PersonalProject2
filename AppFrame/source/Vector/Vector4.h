#pragma once

namespace Vec4
{
	/// @brief 4次元ベクトルクラス
	class Vector4
	{
	public:

		Vector4();
		Vector4(float x, float y, float z);
		Vector4(float x, float y, float z, float w);

		Vector4(const Vector4&) = default;
		Vector4(Vector4&&) = default;
		~Vector4() = default;

		// ===========================================================================
		// 演算子オーバーロード
		// ===========================================================================

		/// @brief コピー代入演算子
		///
		/// @param rhs 代入するベクトル
		/// 
		/// @return 代入後のベクトル
		Vector4& operator=(const Vector4&) = default;

		/// @brief ムーブ代入演算子
		///
		/// @param rhs 代入するベクトル
		/// 
		/// @return 代入後のベクトル
		Vector4& operator=(Vector4&&) = default;

		/// @brief 加算演算子
		///
		/// @param v 加算するベクトル
		/// 
		/// @return 加算結果のベクトル
		Vector4 operator+(const Vector4& v) const;

		/// @brief 減算演算子
		///
		/// @param v 減算するベクトル
		/// 
		/// @return 減算結果のベクトル
		Vector4 operator-(const Vector4& v) const;

		/// @brief 乗算演算子
		///
		/// @param v 乗算するスカラー値
		/// 
		/// @return 乗算結果のベクトル
		Vector4 operator*(float v) const;

		/// @brief 除算演算子
		///
		/// @param v 除算するスカラー値
		/// 
		/// @return 除算結果のベクトル
		Vector4 operator/(float v) const;
	
		/// @brief 加算代入演算子
		///
		/// @param v 加算するベクトル
		/// 
		/// @return 加算後のベクトル
		Vector4& operator+=(const Vector4& v);

		/// @brief 減算代入演算子
		///
		/// @param v 減算するベクトル
		/// 
		/// @return 減算後のベクトル
		Vector4& operator-=(const Vector4& v);
		
		/// @brief 乗算代入演算子
		///
		/// @param v 乗算するスカラー値
		/// 
		/// @return 乗算後のベクトル
		Vector4& operator*=(float v);

		/// @brief 除算代入演算子
		///
		/// @param v 除算するスカラー値
		/// 
		/// @return 除算後のベクトル
		Vector4& operator/=(float v);

		//===========================================================================
		// ゲッター
		//===========================================================================

		float GetX() const { return m_x; }
		float GetY() const { return m_y; }
		float GetZ() const { return m_z; }
		float GetW() const { return m_w; }
		Vector4 Get() const { return Vector4(m_x, m_y, m_z, m_w); }

		//===========================================================================
		// セッター
		//===========================================================================

		void SetX(float x) { m_x = x; }
		void SetY(float y) { m_y = y; }
		void SetZ(float z) { m_z = z; }
		void SetW(float w) { m_w = w; }
		void Set(const Vector4& v);

		//===========================================================================
		// 内部関数
		//===========================================================================

		/// @brief ベクトルを加算する関数
		/// 
		/// @param otherV 加算するベクトル
		/// 
		/// @return 加算結果のベクトル
		Vector4 Add(const Vector4& otherV);

		/// @brief ベクトルを減算する関数
		///
		/// @param otherV 減算するベクトル
		/// 
		/// @return 減算結果のベクトル
		Vector4 Sub(const Vector4& otherV);

		/// @brief ベクトルの長さを計算する関数
		///
		/// @return ベクトルの長さ
		float Length() const;

		/// @brief 正規化されたベクトルを返す関数
		/// 
		/// @return 正規化されたベクトル
		Vector4 Normalize() const;

		/// @brief 2つのベクトルの内積を計算する関数
		/// 
		/// @param v 内積を計算するベクトル
		/// 
		/// @return 内積の値
		float Dot(const Vector4& otherV) const;

	private:

		float m_x = 0.0f;
		float m_y = 0.0f;
		float m_z = 0.0f;
		float m_w = 0.0f;

	};
}