#include "Vector4.h"
#include <cmath>

namespace Vec4
{
	Vector4::Vector4() 
		: 
		m_x(0.0f),
		m_y(0.0f), 
		m_z(0.0f), 
		m_w(1.0f)
	{

	}

	Vector4::Vector4(float x, float y, float z)
		: 
		m_x(x),
		m_y(y), 
		m_z(z), 
		m_w(1.0f)
	{

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: 
		m_x(x),
		m_y(y), 
		m_z(z), 
		m_w(w)
	{

	}

	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(m_x + v.GetX(), m_y + v.GetY(), m_z + v.GetZ(), m_w + v.GetW());
	}

	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(m_x - v.GetX(), m_y - v.GetY(), m_z - v.GetZ(), m_w - v.GetW());
	}

	Vector4 Vector4::operator*(float v) const
	{
		return Vector4(m_x * v, m_y * v, m_z * v, m_w * v);
	}

	Vector4 Vector4::operator/(float v) const
	{
		return Vector4(m_x / v, m_y / v, m_z / v, m_w / v);
	}

	Vector4& Vector4::operator+=(const Vector4& v)
	{
		m_x += v.GetX();
		m_y += v.GetY();
		m_z += v.GetZ();
		m_w += v.GetW();

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& v)
	{
		m_x -= v.GetX();
		m_y -= v.GetY();
		m_z -= v.GetZ();
		m_w -= v.GetW();

		return *this;
	}

	Vector4& Vector4::operator*=(float v)
	{
		m_x *= v;
		m_y *= v;
		m_z *= v;
		m_w *= v;

		return *this;
	}

	Vector4& Vector4::operator/=(float v)
	{
		m_x /= v;
		m_y /= v;
		m_z /= v;
		m_w /= v;

		return *this;
	}

	void Vector4::Set(const Vector4& v)
	{
		m_x = v.GetX();
		m_y = v.GetY();
		m_z = v.GetZ();
		m_w = v.GetW();
	}

	Vector4 Vector4::Add(const Vector4& v1, const Vector4& v2)
	{
		return Vector4
		(
			v1.GetX() + v2.GetX(),
			v1.GetY() + v2.GetY(),
			v1.GetZ() + v2.GetZ(),
			v1.GetW() + v2.GetW()
		);
	}

	Vector4 Vector4::Sub(const Vector4& v1, const Vector4& v2)
	{
		return Vector4
		(
			v1.GetX() - v2.GetX(),
			v1.GetY() - v2.GetY(),
			v1.GetZ() - v2.GetZ(),
			v1.GetW() - v2.GetW()
		);
	}

	float Vector4::Length(const Vector4& v)
	{
		return std::sqrt
		(
			v.GetX() * v.GetX() +
			v.GetY() * v.GetY() +
			v.GetZ() * v.GetZ() +
			v.GetW() * v.GetW()
		);
	}

	Vector4 Vector4::Norm(const Vector4& v)
	{
		float len = Length(v);
		if (len > 0.0f)
		{
			float nx = v.GetX() / len;
			float ny = v.GetY() / len;
			float nz = v.GetZ() / len;
			float nw = v.GetW() / len;

			return Vector4(nx, ny, nz, nw);
		}

		return Vector4(m_x, m_y, m_z, m_w);
	}

	float Vector4::Dot(const Vector4& v1, const Vector4& v2)
	{
		return v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ() + v1.GetW() * v2.GetW();
	}
}
