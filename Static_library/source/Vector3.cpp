#include "Vector3.h"
#include <math.h>

//\=====================================================================
//\ Default Constructor
//\=====================================================================
Vector3::Vector3()
{
	x = 0.f; y = 0.f; z = 0.f;
}
//\=====================================================================
//\ Constructor with X, Y values
//\=====================================================================
Vector3::Vector3(const float a_x, const float a_y, const float a_z)
{
	x = a_x;
	y = a_y;
	z = a_z;
}
//\=====================================================================
//\ Copy Constructor
//\=====================================================================
Vector3::Vector3(const Vector3& a_v3)
{
	x = a_v3.x;
	y = a_v3.y;
	z = a_v3.z;
}
//\=====================================================================
//\ Destructor
//\=====================================================================
Vector3::~Vector3()
{
	// Nothing new to delete
}
//\=====================================================================
//\ Equivalence Operators
//\=====================================================================
bool Vector3::operator== (const Vector3& a_v3) const
{
	return (x == a_v3.x && y == a_v3.y && z == a_v3.z);
}

bool Vector3::operator!= (const Vector3& a_v3) const
{
	return (x != a_v3.x || y != a_v3.y || z != a_v3.z);
}
//\=====================================================================
//\ Negative Operator
//\=====================================================================
const Vector3 Vector3::operator- () const
{
	return Vector3(-x, -y, -z);
}
//\=====================================================================
//\ Overload Operators for Vector2 addition
//\=====================================================================
Vector3 Vector3::operator+ (const Vector3& a_v3) const
{
	return Vector3(x + a_v3.x, y + a_v3.y, z + a_v3.z);
}
Vector3 Vector3::operator+(const float a_scalar) const
{
	return Vector3(x + a_scalar, y + a_scalar, z + a_scalar);
}
Vector3 Vector3::operator- (const Vector3& a_v3) const
{
	return Vector3(x - a_v3.x, y - a_v3.y, z - a_v3.z);
}
Vector3 Vector3::operator-(const float a_scalar) const
{
	return Vector3(x - a_scalar, y - a_scalar, z - a_scalar);
}

//\=====================================================================
//\ Dot Product:the projection of one vector along another or
//\				the cosine value of the angle between two vectors
//\=====================================================================
float Vector3::Dot(const Vector3& a_v3) const
{
	return (x * a_v3.x + y * a_v3.y + z * a_v3.z);
}
//\=====================================================================
//\ Dot Product:Friend function allows us to do the folloiwng in code
//\				Vector3 result = Dot( vec2A, vec2B );
//\				notice the lack of "Vector2::" prior to the function name
//\=====================================================================
float Dot(const Vector3& a_v3A, const Vector3& a_v3B)
{
	return a_v3A.Dot(a_v3B);
}

Vector3 Vector3::Cross(const Vector3& a_v3) const
{
	return Vector3(y * a_v3.z - z * a_v3.y, z * a_v3.x - x * a_v3.z, x * a_v3.y - y * a_v3.x);
}
Vector3	Cross(const Vector3& a_v3, const Vector3& a_v3b)
{
	return a_v3.Cross(a_v3b);
}
//\=====================================================================
//\ Overload Operators for Vector2 muliplication
//\=====================================================================
Vector3 Vector3::operator*(const float& a_scalar) const
{
	return Vector3(x * a_scalar, y * a_scalar, z * a_scalar);
}

Vector3 Vector3::operator*(const Vector3& a_v3) const
{
	return Vector3(x * a_v3.x, y * a_v3.y, z * a_v3.z);
}

//\===================================================================================
//\ Get length (magnitude) of the vector
//\===================================================================================
float Vector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);	// to access SQRTF #include <math.h>
}
//\===================================================================================
//\ Normalise the vector
//\===================================================================================
void Vector3::Normalize()
{
	float length = Length();
	if (length > 0.f)			// if this is false, vector has no length
	{
		float invLen = 1.f / length;
		x *= invLen;
		y *= invLen;
		z *= invLen;
	}
}

Vector3	Vector3::Normalized()
{
	this->Normalize();
	return *this;
}

Vector3	Normalize(const Vector3& a_v3)
{
	float length = a_v3.Length();
	if (length > 0.f)			// if this is false, vector has no length
	{
		float invLen = 1.f / length;
		return Vector3( a_v3.x * invLen, a_v3.y * invLen, a_v3.z *invLen);
	}
	return Vector3(0.f, 0.f, 0.f);
}
//\===================================================================================
//\ Linear Interpolation
//\===================================================================================
Vector3 Lerp(const Vector3 & a_v3A, const Vector3 & a_v3B, const float a_t)
{
	return (a_v3B - a_v3A) * a_t + a_v3A;
}
//\===================================================================================
//\ Reflect one vector around another
//\===================================================================================
Vector3 Reflect(const Vector3& a_v3A, const Vector3& a_v3B)								// friend function
{
	Vector3 reflect = a_v3A - a_v3B * 2.f * Dot(a_v3A, a_v3B);
	return reflect;
}
//\===================================================================================
//\ Compound assignment operator
//\===================================================================================
Vector3	Vector3::operator += (const Vector3& a_v3)
{
	x += a_v3.x;
	y += a_v3.y;
	z += a_v3.z;
	return *this;
}
