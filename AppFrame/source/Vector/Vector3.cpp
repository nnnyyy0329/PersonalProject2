#include "Vector3.h"
#include <cmath>

namespace Vec3
{
	Vector3::Vector3()
		:
		m_x(0.0f),
		m_y(0.0f),
		m_z(0.0f)
	{

	}

	Vector3::Vector3(float x, float y, float z)
		:
		m_x(x),
		m_y(y),
		m_z(z)
	{

	}

	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(m_x + v.GetX(), m_y + v.GetY(), m_z + v.GetZ());
	}

	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(m_x - v.GetX(), m_y - v.GetY(), m_z - v.GetZ());
	}

	Vector3 Vector3::operator*(float v) const
	{
		return Vector3(m_x * v, m_y * v, m_z * v);
	}

	Vector3 Vector3::operator/(float v) const
	{
		return Vector3(m_x / v, m_y / v, m_z / v);
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		m_x += v.GetX();
		m_y += v.GetY();
		m_z += v.GetZ();

		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& v)
	{
		m_x -= v.GetX();
		m_y -= v.GetY();
		m_z -= v.GetZ();
		return *this;
	}

	Vector3& Vector3::operator*=(float v)
	{
		m_x *= v;
		m_y *= v;
		m_z *= v;

		return *this;
	}

	Vector3& Vector3::operator/=(float v)
	{
		m_x /= v;
		m_y /= v;
		m_z /= v;

		return *this;
	}

	void Vector3::Set(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	void Vector3::Set(const Vector3& v)
	{
		m_x = v.GetX();
		m_y = v.GetY();
		m_z = v.GetZ();
	}

	Vector3 Vector3::Add(const Vector3& otherV)
	{
		return Vector3(m_x + otherV.GetX(), m_y + otherV.GetY(), m_z + otherV.GetZ());
	}

	Vector3 Vector3::Sub(const Vector3& otherV)
	{
		return Vector3(m_x - otherV.GetX(), m_y - otherV.GetY(), m_z - otherV.GetZ());
	}

	Vector3 Vector3::Normalize() const
	{
		float len = Length();
		if(len > 0.0f)
		{
			float nx = m_x / len;
			float ny = m_y / len;
			float nz = m_z / len;

			return Vector3(nx, ny, nz);
		}

		return Vector3(m_x, m_y, m_z);
	}

	Vector3 Vector3::Cross(const Vector3& otherV) const
	{
		float cx = m_y * otherV.GetZ() - m_z * otherV.GetY();
		float cy = m_z * otherV.GetX() - m_x * otherV.GetZ();
		float cz = m_x * otherV.GetY() - m_y * otherV.GetX();

		return Vector3(cx, cy, cz);
	}

	float Vector3::Dot(const Vector3& otherV) const
	{
		return m_x * otherV.GetX() + m_y * otherV.GetY() + m_z * otherV.GetZ();
	}

	float Vector3::Length() const
	{
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	float Vector3::LengthSq() const
	{
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

}