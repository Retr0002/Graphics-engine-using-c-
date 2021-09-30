#include "Vector2.h"

//\==========================================================================
// Default Constructor
//\==========================================================================
Vector2::Vector2()
{
	x = 0.f; y = 0.f;
}
//\==========================================================================
// Constructor with X & Y values
//\==========================================================================
Vector2::Vector2(const float a_x, const float a_y)
{
	x = a_x;
	y = a_y;
}
//\==========================================================================
// Copy Constructor
//\==========================================================================
Vector2::Vector2(const Vector2& a_v2)
{
	x = a_v2.x;
	y = a_v2.y;
}
//\==========================================================================
// Destructor
//\==========================================================================
Vector2::~Vector2()
{
	// Nothing to delete
}
//\==========================================================================
// Equivalence Operators
//\==========================================================================
bool Vector2::operator==(const Vector2& a_v2) const
{
	return (x == a_v2.x && y == a_v2.y);
}

bool Vector2::operator!=(const Vector2& a_v2) const
{
	return (x != a_v2.x || y != a_v2.y);
}
//\==========================================================================
// Negative Operator
//\==========================================================================
const Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}
//\==========================================================================
// Overload Operators for Vector2 addition
//\==========================================================================
Vector2 Vector2::operator+(const Vector2& a_v2) const
{
	return Vector2(x + a_v2.x, y + a_v2.y);
}
//\==========================================================================
// Dot Product -	projection of one vector along another or
//					the consine value of the angle between 2 vectors
//\==========================================================================
float Vector2::Dot(const Vector2& a_v2) const
{
	return (x * a_v2.x + y * a_v2.y);
}
//\==========================================================================
// Dot Product -	Friend function allows us to do the following in code:
//					Vector2 result = Dot(vec2A, vec2B);
//					Note lack of "Vector2::" before the function name
//\==========================================================================
float Dot(const Vector2& a_v2A, const Vector2& a_v2B)
{
	return a_v2A.Dot(a_v2B);
}
