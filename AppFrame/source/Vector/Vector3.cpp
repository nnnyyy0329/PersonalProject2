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

	void Vector3::Set(const Vector3& v)
	{
		m_x = v.GetX();
		m_y = v.GetY();
		m_z = v.GetZ();
	}

	Vector3 Vector3::Add(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.GetX() + v2.GetX(), v1.GetY() + v2.GetY(), v1.GetZ() + v2.GetZ());
	}

	Vector3 Vector3::Sub(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.GetX() - v2.GetX(), v1.GetY() - v2.GetY(), v1.GetZ() - v2.GetZ());
	}

	float Vector3::Length(const Vector3& v)
	{
		return std::sqrt
		(
			v.GetX() * v.GetX() +
			v.GetY() * v.GetY() +
			v.GetZ() * v.GetZ()
		);
	}

	Vector3 Vector3::Norm(const Vector3& v)
	{
		float len = Length(v);
		if(len > 0.0f)
		{
			float nx = v.GetX() / len;
			float ny = v.GetY() / len;
			float nz = v.GetZ() / len;

			return Vector3(nx, ny, nz);
		}

		return Vector3(m_x, m_y, m_z);
	}

	float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.GetX() * v2.GetX() + v1.GetY() * v2.GetY() + v1.GetZ() * v2.GetZ();
	}

}