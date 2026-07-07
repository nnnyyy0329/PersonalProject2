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

	Vector4 Vector4::Add(const Vector4& otherV)
	{
		return Vector4
		(
			m_x + otherV.GetX(),
			m_y + otherV.GetY(),
			m_z + otherV.GetZ(),
			m_w + otherV.GetW()
		);
	}

	Vector4 Vector4::Sub(const Vector4& otherV)
	{
		return Vector4
		(
			m_x - otherV.GetX(),
			m_y - otherV.GetY(),
			m_z - otherV.GetZ(),
			m_w - otherV.GetW()
		);
	}

	float Vector4::Length() const
	{
		return std::sqrt
		(
			m_x * m_x +
			m_y * m_y +
			m_z * m_z +
			m_w * m_w
		);
	}

	Vector4 Vector4::Normalize() const
	{
		float len = Length();
		if (len > 0.0f)
		{
			float nx = m_x / len;
			float ny = m_y / len;
			float nz = m_z / len;
			float nw = m_w / len;

			return Vector4(nx, ny, nz, nw);
		}

		return Vector4(m_x, m_y, m_z, m_w);
	}

	float Vector4::Dot(const Vector4& otherV) const
	{
		return m_x * otherV.GetX() + m_y * otherV.GetY() + m_z * otherV.GetZ() + m_w * otherV.GetW();
	}
}
