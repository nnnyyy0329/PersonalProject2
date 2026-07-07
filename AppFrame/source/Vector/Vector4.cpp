#include "Vector4.h"
#include <cmath>

namespace Vector
{
	Vector4::Vector4() 
		: 
		_x(0.0f), 
		_y(0.0f), 
		_z(0.0f), 
		_w(1.0f)
	{

	}

	Vector4::Vector4(float x, float y, float z)
		: 
		_x(x),
		_y(y), 
		_z(z), 
		_w(1.0f)
	{

	}

	Vector4::Vector4(float x, float y, float z, float w)
		: 
		_x(x),
		_y(y), 
		_z(z), 
		_w(w)
	{

	}

	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(_x + v.GetX(), _y + v.GetY(), _z + v.GetZ());
	}

	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(_x - v.GetX(), _y - v.GetY(), _z - v.GetZ());
	}

	Vector4 Vector4::operator*(float v) const
	{
		return Vector4(_x * v, _y * v, _z * v);
	}

	Vector4 Vector4::operator/(float v) const
	{
		return Vector4(_x / v, _y / v, _z / v);
	}

	Vector4& Vector4::operator+=(const Vector4& v)
	{
		_x += v.GetX();
		_y += v.GetY();
		_z += v.GetZ();

		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& v)
	{
		_x -= v.GetX();
		_y -= v.GetY();
		_z -= v.GetZ();

		return *this;
	}

	Vector4& Vector4::operator*=(float v)
	{
		_x *= v;
		_y *= v;
		_z *= v;

		return *this;
	}

	Vector4& Vector4::operator/=(float v)
	{
		_x /= v;
		_y /= v;
		_z /= v;

		return *this;
	}

	void Vector4::Set(const Vector4& v)
	{
		_x = v.GetX();
		_y = v.GetY();
		_z = v.GetZ();
		_w = v.GetW();
	}

	Vector4 Vector4::Add(const Vector4& v)
	{
		return Vector4(_x + v.GetX(), _y + v.GetY(), _z + v.GetZ());
	}

	Vector4 Vector4::Sub(const Vector4& v)
	{
		return Vector4(_x - v.GetX(), _y - v.GetY(), _z - v.GetZ());
	}

	float Vector4::Length() const
	{
		return std::sqrt(_x * _x + _y * _y + _z * _z);
	}

	Vector4 Vector4::Normalized() const
	{
		float len = Length();
		if (len > 0.0f)
		{
			float nx = _x / len;
			float ny = _y / len;
			float nz = _z / len;

			return Vector4(nx, ny, nz);
		}

		return Vector4(_x, _y, _z);
	}

	float Vector4::Dot(const Vector4& v) const
	{
		return _x * v.GetX() + _y * v.GetY() + _z * v.GetZ();
	}
}
