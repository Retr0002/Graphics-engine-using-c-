#include "Matrix4.h"

//\=====================================================================================
//A constant static variable to use to quickly set/get an identity matrix
//\=====================================================================================
const Matrix4 Matrix4::IDENTITY = Matrix4(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

//\=====================================================================================
//\ Default Constructor - by default init to identity
//\=====================================================================================

//Had Column and row mixedup -Fixed
Matrix4::Matrix4() :m_11(1.f), m_21(0.f), m_31(0.f), m_41(0.f),
					m_12(0.f), m_22(1.f), m_32(0.f), m_42(0.f),
					m_13(0.f), m_23(0.f), m_33(1.f), m_43(0.f),
					m_14(0.f), m_24(0.f), m_34(0.f), m_44(1.f)
{
}

//\=====================================================================================
//\ Constructor using pointer to float data
//\=====================================================================================
Matrix4::Matrix4(const float* a_mat) :	m_11(a_mat[0]), m_21(a_mat[1]), m_31(a_mat[2]), m_41(a_mat[3]),
										m_12(a_mat[4]), m_22(a_mat[5]), m_32(a_mat[6]), m_42(a_mat[7]),
										m_13(a_mat[8]), m_23(a_mat[9]), m_33(a_mat[10]), m_43(a_mat[11]),
										m_14(a_mat[12]), m_24(a_mat[13]), m_34(a_mat[14]), m_44(a_mat[15])
{
}
//\=====================================================================================
//\ Constructor using all components of matrix data structure
//\=====================================================================================
Matrix4::Matrix4(	float a_m11, float a_m21, float a_m31, float a_m41,
					float a_m12, float a_m22, float a_m32, float a_m42,
					float a_m13, float a_m23, float a_m33, float a_m43,
					float a_m14, float a_m24, float a_m34, float a_m44) :
					m_11(a_m11), m_21(a_m21), m_31(a_m31), m_41(a_m41),
					m_12(a_m12), m_22(a_m22), m_32(a_m32), m_42(a_m42),
					m_13(a_m13), m_23(a_m23), m_33(a_m33), m_43(a_m43),
					m_14(a_m14), m_24(a_m24), m_34(a_m34), m_44(a_m44)
{
}
//\=====================================================================================
//\ Construct form Axis angle vectors
//\=====================================================================================
Matrix4::Matrix4(const Vector4& a_xAxis, const Vector4& a_yAxis, const Vector4& a_zAxis, const Vector4& a_wAxis) :
	m_xAxis(a_xAxis), m_yAxis(a_yAxis), m_zAxis(a_zAxis), m_wAxis(a_wAxis)
{
}
//\=====================================================================================
// Copy Constructor
//\=====================================================================================
Matrix4::Matrix4(const Matrix4& a_m4) :
	m_11(a_m4.m_11), m_21(a_m4.m_21), m_31(a_m4.m_31), m_41(a_m4.m_41),
	m_12(a_m4.m_12), m_22(a_m4.m_22), m_32(a_m4.m_32), m_42(a_m4.m_42),
	m_13(a_m4.m_13), m_23(a_m4.m_23), m_33(a_m4.m_33), m_43(a_m4.m_43),
	m_14(a_m4.m_14), m_24(a_m4.m_24), m_34(a_m4.m_34), m_44(a_m4.m_44)
{
}
//\=====================================================================================
//\ Destructor
//\=====================================================================================
Matrix4::~Matrix4()
{
}

//\=====================================================================================
//\ Member variable access operator overload
//\=====================================================================================
#include <cassert>
float& Matrix4::operator() (int a_row, int a_col)
{
	//Make sure that column and row is within range 
	assert(a_col >= 0 && a_col < 4);
	assert(a_row >= 0 && a_row < 4);
	return m[a_col - 1][a_row - 1];
}

float Matrix4::operator() (int a_iRow, int a_iCol) const
{
	//Make sure that column and row is within range 
	assert(a_iCol >= 0 && a_iCol < 4);
	assert(a_iRow >= 0 && a_iRow < 4);
	return m[a_iCol - 1][a_iRow - 1];
}
//\=====================================================================================
//\ Column and Row Access
//\=====================================================================================
void Matrix4::SetColumn(int a_iCol, const Vector4& a_vCol)
{
	assert(a_iCol >= 0 && a_iCol < 4);
	m[a_iCol][0] = a_vCol.x; m[a_iCol][1] = a_vCol.y; m[a_iCol][2] = a_vCol.z; m[a_iCol][3] = a_vCol.w;

}

//Had trouble with GetColumn on a Vector3, fixed by converting V4 to V3 on GetColumn after output
Vector4	Matrix4::GetColumn(int a_iCol) const
{
	assert(a_iCol >= 0 && a_iCol < 4);
	return Vector4(m[a_iCol][0], m[a_iCol][1], m[a_iCol][2], m[a_iCol][3]);
}
//\===========================================================================================
//\ Equivalence Operators
//\===========================================================================================
bool Matrix4::operator  ==	(const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return false; }
	if (m_21 != a_m4.m_21) { return false; }
	if (m_31 != a_m4.m_31) { return false; }
	if (m_41 != a_m4.m_41) { return false; }
	if (m_12 != a_m4.m_12) { return false; }
	if (m_22 != a_m4.m_22) { return false; }
	if (m_32 != a_m4.m_32) { return false; }
	if (m_42 != a_m4.m_42) { return false; }
	if (m_13 != a_m4.m_13) { return false; }
	if (m_23 != a_m4.m_23) { return false; }
	if (m_33 != a_m4.m_33) { return false; }
	if (m_43 != a_m4.m_43) { return false; }
	if (m_14 != a_m4.m_14) { return false; }
	if (m_24 != a_m4.m_24) { return false; }
	if (m_34 != a_m4.m_34) { return false; }
	if (m_44 != a_m4.m_44) { return false; }
	return true;
}

bool Matrix4::operator  !=	(const Matrix4& a_m4) const
{
	if (m_11 != a_m4.m_11) { return true; }
	if (m_21 != a_m4.m_21) { return true; }
	if (m_31 != a_m4.m_31) { return true; }
	if (m_41 != a_m4.m_41) { return true; }
	if (m_12 != a_m4.m_12) { return true; }
	if (m_22 != a_m4.m_22) { return true; }
	if (m_32 != a_m4.m_32) { return true; }
	if (m_42 != a_m4.m_42) { return true; }
	if (m_13 != a_m4.m_13) { return true; }
	if (m_23 != a_m4.m_23) { return true; }
	if (m_33 != a_m4.m_33) { return true; }
	if (m_43 != a_m4.m_43) { return true; }
	if (m_14 != a_m4.m_14) { return true; }
	if (m_24 != a_m4.m_24) { return true; }
	if (m_34 != a_m4.m_34) { return true; }
	if (m_44 != a_m4.m_44) { return true; }
	return false;
}
//\===========================================================================================
//\ Operator overloads for Addition
//\===========================================================================================
Matrix4 Matrix4::operator+(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 + a_m4.m_11, m_21 + a_m4.m_21, m_31 + a_m4.m_31, m_41 + a_m4.m_41,
					m_12 + a_m4.m_12, m_22 + a_m4.m_22, m_32 + a_m4.m_32, m_42 + a_m4.m_42,
					m_13 + a_m4.m_13, m_23 + a_m4.m_23, m_33 + a_m4.m_33, m_43 + a_m4.m_43,
					m_14 + a_m4.m_14, m_24 + a_m4.m_24, m_34 + a_m4.m_34, m_44 + a_m4.m_44);
}

const Matrix4& Matrix4::operator+=(const Matrix4& a_m4)
{
	m_11 += a_m4.m_11; m_12 += a_m4.m_12; m_13 += a_m4.m_13; m_14 += a_m4.m_14;
	m_21 += a_m4.m_21; m_22 += a_m4.m_22; m_23 += a_m4.m_23; m_24 += a_m4.m_24;
	m_31 += a_m4.m_31; m_32 += a_m4.m_32; m_33 += a_m4.m_33; m_34 += a_m4.m_34;
	m_41 += a_m4.m_41; m_42 += a_m4.m_42; m_43 += a_m4.m_43; m_44 += a_m4.m_44;
	return *this;
}
//\===========================================================================================
//\ Operator overloads for Subtraction
//\===========================================================================================
Matrix4 Matrix4::operator-(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 - a_m4.m_11, m_21 - a_m4.m_21, m_31 - a_m4.m_31, m_41 - a_m4.m_41,
					m_12 - a_m4.m_12, m_22 - a_m4.m_22, m_32 - a_m4.m_32, m_42 - a_m4.m_42,
					m_13 - a_m4.m_13, m_23 - a_m4.m_23, m_33 - a_m4.m_33, m_43 - a_m4.m_43,
					m_14 - a_m4.m_14, m_24 - a_m4.m_24, m_34 - a_m4.m_43, m_44 - a_m4.m_44);
}

const Matrix4& Matrix4::operator-=(const Matrix4& a_m4)
{
	m_11 -= a_m4.m_11; m_12 -= a_m4.m_12; m_13 -= a_m4.m_13; m_14 -= a_m4.m_14;
	m_21 -= a_m4.m_21; m_22 -= a_m4.m_22; m_23 -= a_m4.m_23; m_24 -= a_m4.m_24;
	m_31 -= a_m4.m_31; m_32 -= a_m4.m_32; m_33 -= a_m4.m_33; m_34 -= a_m4.m_34;
	m_41 -= a_m4.m_41; m_42 -= a_m4.m_42; m_43 -= a_m4.m_43; m_44 -= a_m4.m_44;
	return *this;
}
//\===========================================================================================
//\ Operator overloads for multiplication by scalar value
//\===========================================================================================
//Maths on * operator was wrong as it returned it the wrong way round
Matrix4 Matrix4::operator*(const float a_fScalar) const
{
	return Matrix4(	m_11 * a_fScalar, m_12 * a_fScalar, m_13 * a_fScalar, m_14 * a_fScalar,
					m_21 * a_fScalar, m_22 * a_fScalar, m_23 * a_fScalar, m_24 * a_fScalar,
					m_31 * a_fScalar, m_32 * a_fScalar, m_33 * a_fScalar, m_34 * a_fScalar,
					m_41 * a_fScalar, m_42 * a_fScalar, m_34 * a_fScalar, m_44 * a_fScalar);
}

const Matrix4& Matrix4::operator*=(float a_fScalar)
{
	m_11 *= a_fScalar; m_12 *= a_fScalar; m_13 *= a_fScalar; m_14 *= a_fScalar;
	m_21 *= a_fScalar; m_22 *= a_fScalar; m_23 *= a_fScalar; m_24 *= a_fScalar;
	m_31 *= a_fScalar; m_32 *= a_fScalar; m_33 *= a_fScalar; m_34 *= a_fScalar;
	m_41 *= a_fScalar; m_42 *= a_fScalar; m_43 *= a_fScalar; m_44 *= a_fScalar;
	return *this;
}
//\===========================================================================================
//\ Operator overloads for multiplication by vector4 value
//\===========================================================================================
Vector4 Matrix4::operator*(const Vector4& a_v4) const
{
	return Vector4(	m_11 * a_v4.x + m_12 * a_v4.y + m_13 * a_v4.z + m_14 * a_v4.w,
					m_21 * a_v4.x + m_22 * a_v4.y + m_23 * a_v4.z + m_24 * a_v4.w,
					m_31 * a_v4.x + m_32 * a_v4.y + m_33 * a_v4.z + m_34 * a_v4.w,
					m_41 * a_v4.x + m_42 * a_v4.y + m_43 * a_v4.z + m_44 * a_v4.w);
}
//\===========================================================================================
//\ Operator overloads for multiplication by Matrix4
//\===========================================================================================
Matrix4 Matrix4::operator*(const Matrix4& a_m4) const
{
	return Matrix4(	m_11 * a_m4.m_11 + m_12 * a_m4.m_21 + m_13 * a_m4.m_31 + m_14 * a_m4.m_41,
					m_21 * a_m4.m_11 + m_22 * a_m4.m_21 + m_23 * a_m4.m_31 + m_24 * a_m4.m_41,
					m_31 * a_m4.m_11 + m_32 * a_m4.m_21 + m_33 * a_m4.m_31 + m_34 * a_m4.m_41,
					m_41 * a_m4.m_11 + m_42 * a_m4.m_21 + m_43 * a_m4.m_31 + m_44 * a_m4.m_41,

					m_11 * a_m4.m_12 + m_12 * a_m4.m_22 + m_13 * a_m4.m_32 + m_14 * a_m4.m_42,
					m_21 * a_m4.m_12 + m_22 * a_m4.m_22 + m_23 * a_m4.m_32 + m_24 * a_m4.m_42,
					m_31 * a_m4.m_12 + m_32 * a_m4.m_22 + m_33 * a_m4.m_32 + m_34 * a_m4.m_42,
					m_41 * a_m4.m_12 + m_42 * a_m4.m_22 + m_43 * a_m4.m_32 + m_44 * a_m4.m_42,

					m_11 * a_m4.m_13 + m_12 * a_m4.m_23 + m_13 * a_m4.m_33 + m_14 * a_m4.m_43,
					m_21 * a_m4.m_13 + m_22 * a_m4.m_23 + m_23 * a_m4.m_33 + m_24 * a_m4.m_43,
					m_31 * a_m4.m_13 + m_32 * a_m4.m_23 + m_33 * a_m4.m_33 + m_34 * a_m4.m_43,
					m_41 * a_m4.m_13 + m_42 * a_m4.m_23 + m_43 * a_m4.m_33 + m_44 * a_m4.m_43,
		
					m_11 * a_m4.m_14 + m_12 * a_m4.m_24 + m_13 * a_m4.m_34 + m_14 * a_m4.m_44,
					m_21 * a_m4.m_14 + m_22 * a_m4.m_24 + m_23 * a_m4.m_34 + m_24 * a_m4.m_44,
					m_31 * a_m4.m_14 + m_32 * a_m4.m_24 + m_33 * a_m4.m_34 + m_34 * a_m4.m_44,
					m_41 * a_m4.m_14 + m_42 * a_m4.m_24 + m_43 * a_m4.m_34 + m_44 * a_m4.m_44);
}

const Matrix4& Matrix4::operator*=(const Matrix4& a_m4)
{
	*this = (*this) * a_m4;
	return *this;
}

//\===========================================================================================
//\ Transpose Matrix - Transform from Row to Column
//\===========================================================================================
void Matrix4::Transpose()
{
	float k;
	k = m_12; m_12 = m_21; m_21 = k;
	k = m_13; m_13 = m_31; m_31 = k;
	k = m_14; m_14 = m_41; m_41 = k;
	k = m_23; m_23 = m_32; m_32 = k;
	k = m_24; m_24 = m_42; m_42 = k;
	k = m_34; m_34 = m_43; m_43 = k;
}

Matrix4 Matrix4::GetTranspose() const
{
	return Matrix4(	m_11, m_12, m_13, m_14,
					m_21, m_22, m_23, m_24,
					m_31, m_32, m_33, m_34,
					m_41, m_42, m_43, m_44);
}
//\===========================================================================================
//\ Scale Functionality
//\===========================================================================================
void Matrix4::Scale(const Vector4& a_v4)
{
	m_11 = a_v4.x;	m_12 = 0.0f;	m_13 = 0.0f;	m_14 = 0.0f;
	m_21 = 0.0f;	m_22 = a_v4.y;	m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = 0.0f;	m_32 = 0.0f;	m_33 = a_v4.z;	m_34 = 0.0f;
	m_41 = 0.0f;	m_42 = 0.0f;	m_34 = 0.0f;	m_44 = 1.f;
}

void Matrix4::Scale(float a_fScalar)
{
	Scale(Vector4(a_fScalar, a_fScalar, a_fScalar, 1.f));
}
//\===========================================================================================
//\ General matrix functions
//\===========================================================================================
void Matrix4::Identity()
{
	m_11 = 1.0f;	m_12 = 0.0f;	m_13 = 0.0f;	m_14 = 0.0f;
	m_21 = 0.0f;	m_22 = 1.0f;	m_23 = 0.0f;	m_24 = 0.0f;
	m_31 = 0.0f;	m_32 = 0.0f;	m_33 = 1.0f;	m_34 = 0.0f;
	m_41 = 0.0f;	m_42 = 0.0f;	m_34 = 0.0f;	m_44 = 1.0f;
}

//\===========================================================================================
//\ Inverse Matrix
//\===========================================================================================
float Matrix4::Determinant() const
{
	float fA = m_11 * (m_22 * (m_33 * m_44 - m_34 * m_43) +
		m_23 * (m_34 * m_42 - m_32 * m_44) +
		m_24 * (m_32 * m_43 - m_33 * m_42));

	float fB = m_12 * (m_21 * (m_33 * m_44 - m_34 * m_43) +
		m_23 * (m_34 * m_41 - m_31 * m_44) +
		m_24 * (m_31 * m_43 - m_33 * m_41));

	float fC = m_13 * (m_21 * (m_32 * m_44 - m_34 * m_42) +
		m_22 * (m_34 * m_41 - m_31 * m_44) +
		m_24 * (m_31 * m_42 - m_32 * m_41));

	float fD = m_14 * (m_21 * (m_32 * m_43 - m_33 * m_42) +
		m_22 * (m_33 * m_41 - m_31 * m_43) +
		m_23 * (m_31 * m_42 - m_32 * m_41));

	return  fA - fB + fC - fD;
}


//attempt at making code more efficient by doing calculation beforhand
/*
std::vector<float> Matrix4::GetDetValues() const
{
	std::vector<float> detValues;

	detValues.push_back(m_33 * m_44 - m_34 * m_43); //0
	detValues.push_back(m_34 * m_42 - m_32 * m_44); //1
	detValues.push_back(m_32 * m_43 - m_33 * m_42); //2
	detValues.push_back(m_32 * m_44 - m_34 * m_42); //3
	detValues.push_back(m_34 * m_41 - m_31 * m_44); //4
	detValues.push_back(m_31 * m_43 - m_33 * m_41); //5
	detValues.push_back(m_31 * m_42 - m_32 * m_41); //6
	detValues.push_back(m_34 * m_41 - m_31 * m_44); //7
	detValues.push_back(m_33 * m_44 - m_34 * m_43); //8
	detValues.push_back(m_33 * m_41 - m_31 * m_43); //9
	detValues.push_back(m_23 * m_44 - m_24 * m_43); //10
	detValues.push_back(m_24 * m_42 - m_22 * m_44); //11
	detValues.push_back(m_22 * m_43 - m_23 * m_42); //12
	detValues.push_back(m_22 * m_44 - m_24 * m_42); //13
	detValues.push_back(m_24 * m_41 - m_21 * m_44); //14
	detValues.push_back(m_21 * m_43 - m_23 * m_41); //15
	detValues.push_back(m_21 * m_42 - m_22 * m_41); //16
	detValues.push_back(m_24 * m_41 - m_21 * m_44); //17
	detValues.push_back(m_23 * m_44 - m_24 * m_43); //18
	detValues.push_back(m_23 * m_41 - m_21 * m_43); //19
	return detValues;
}
*/

Matrix4 Matrix4::Inverse()  const
{
	const float fDet = Determinant();
	if (fDet != 0.0f)
	{
		const float fInvDet = 1.f / fDet;

		Matrix4 mat;
		mat.m_11 = (m_22 * (m_33 * m_44 - m_34 * m_43) +
			m_23 * (m_34 * m_42 - m_32 * m_44) +
			m_24 * (m_32 * m_43 - m_33 * m_42)) * fInvDet;

		mat.m_21 = (m_21 * (m_33 * m_44 - m_34 * m_43) +
			m_23 * (m_34 * m_41 - m_31 * m_44) +
			m_24 * (m_31 * m_43 - m_33 * m_41)) * -fInvDet;

		mat.m_31 = (m_21 * (m_32 * m_44 - m_34 * m_42) +
			m_22 * (m_34 * m_41 - m_31 * m_44) +
			m_24 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		mat.m_41 = (m_21 * (m_32 * m_43 - m_33 * m_42) +
			m_22 * (m_33 * m_41 - m_31 * m_43) +
			m_23 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		mat.m_12 = (m_12 * (m_33 * m_44 - m_34 * m_43) +
			m_13 * (m_34 * m_42 - m_32 * m_44) +
			m_14 * (m_32 * m_43 - m_33 * m_42)) * -fInvDet;

		mat.m_22 = (m_11 * (m_33 * m_44 - m_34 * m_43) +
			m_13 * (m_34 * m_41 - m_31 * m_44) +
			m_14 * (m_31 * m_43 - m_33 * m_41)) * fInvDet;

		mat.m_32 = (m_11 * (m_32 * m_44 - m_34 * m_42) +
			m_12 * (m_34 * m_41 - m_31 * m_44) +
			m_14 * (m_31 * m_42 - m_32 * m_41)) * -fInvDet;

		mat.m_42 = (m_11 * (m_32 * m_43 - m_33 * m_42) +
			m_12 * (m_33 * m_41 - m_31 * m_43) +
			m_13 * (m_31 * m_42 - m_32 * m_41)) * fInvDet;

		mat.m_13 = (m_12 * (m_23 * m_44 - m_24 * m_43) +
			m_13 * (m_24 * m_42 - m_22 * m_44) +
			m_14 * (m_22 * m_43 - m_23 * m_42)) * fInvDet;

		mat.m_23 = (m_11 * (m_23 * m_44 - m_24 * m_43) +
			m_13 * (m_24 * m_41 - m_21 * m_44) +
			m_14 * (m_21 * m_43 - m_23 * m_41)) * -fInvDet;

		mat.m_33 = (m_11 * (m_22 * m_44 - m_24 * m_42) +
			m_12 * (m_24 * m_41 - m_21 * m_44) +
			m_14 * (m_21 * m_42 - m_22 * m_41)) * fInvDet;

		mat.m_43 = (m_11 * (m_22 * m_43 - m_23 * m_42) +
			m_12 * (m_23 * m_41 - m_21 * m_43) +
			m_13 * (m_21 * m_42 - m_22 * m_41)) * -fInvDet;

		mat.m_14 = (m_12 * (m_23 * m_34 - m_24 * m_33) +
			m_13 * (m_24 * m_32 - m_22 * m_34) +
			m_14 * (m_22 * m_33 - m_23 * m_32)) * -fInvDet;

		mat.m_24 = (m_11 * (m_23 * m_34 - m_24 * m_33) +
			m_13 * (m_24 * m_31 - m_21 * m_34) +
			m_14 * (m_21 * m_33 - m_23 * m_31)) * fInvDet;

		mat.m_34 = (m_11 * (m_22 * m_34 - m_24 * m_32) +
			m_12 * (m_24 * m_31 - m_21 * m_34) +
			m_14 * (m_21 * m_32 - m_22 * m_31)) * -fInvDet;

		mat.m_44 = (m_11 * (m_22 * m_33 - m_23 * m_32) +
			m_12 * (m_23 * m_31 - m_21 * m_33) +
			m_13 * (m_21 * m_32 - m_22 * m_31)) * fInvDet;

		return mat;
	}
	else
	{
		return Matrix4::IDENTITY;
	}
}
//\==========================================================================
//\ Overload stream operator
//\==========================================================================
std::ostream& operator<<(std::ostream& os, const Matrix4 a_m4)
{
	os.setf(std::ios::fixed, std::ios::floatfield);	// Set fixed precision to force number of decimals
	os.precision(3);								// Set number of decimal places to three
	os << a_m4.m_11 << "\t" << a_m4.m_12 << "\t" << a_m4.m_13 << "\t" << a_m4.m_14 << std::endl;
	os << a_m4.m_21 << "\t" << a_m4.m_22 << "\t" << a_m4.m_23 << "\t" << a_m4.m_24 << std::endl;
	os << a_m4.m_31 << "\t" << a_m4.m_32 << "\t" << a_m4.m_33 << "\t" << a_m4.m_34 << std::endl;
	os << a_m4.m_41 << "\t" << a_m4.m_42 << "\t" << a_m4.m_43 << "\t" << a_m4.m_44 << std::endl;

	return os;
}
//\=========================================================================
//\ Camera Projection Functions
//\ Sets projection matrix following the right-handed (native) way:
//\ 
//\   |  w          0          0          0  |  --> w = aspect ratio * tan(fovy/2)
//\   |  0          h          0          0  |  --> h = cotan(fovy/2)
//\   |  0          0      -(zf+zn)*r    -1  |  --> r = 1/(zn-zf)
//\   |  0          0     -2*(zf*zn)*r    0  |
//\
//\=========================================================================
bool Matrix4::Perspective(float fRadFovY,
	float fAspectRatio,
	float fZNear,
	float fZFar)
{
	float tanHalfFov = tanf(fRadFovY * 0.5f);
	if (fabsf(fZFar - fZNear) < 0.01f)
	{
		return false;
	}
	const float w = 1.f / (fAspectRatio * tanHalfFov);;   // two semi-colons?
	const float h = 1.f / tanHalfFov;

	const float r = 1.0f / (fZFar - fZNear);
	// X-axis column
	m_11 = w;	m_21 = 0.0f;	m_31 = 0.0f;	m_41 = 0.0f;
	// Y-axis column
	m_12 = 0.0f;	m_22 = h;	m_32 = 0.0f;	m_42 = 0.0f;
	// Z-axis column
	m_13 = 0.0f;	m_23 = 0.0f;	m_33 = -(fZFar + fZNear) * r;	m_43 = -1.f;
	// Transpose column
	m_14 = 0.0f;	m_24 = 0.0f;	m_34 = -(2.0f * fZFar * fZNear) * r;	m_44 = 0.0f;

	return true;
}
//\=========================================================================
//\ Sets orthographic projection matrix
//\ OpenGL way:
//\  |  2/r-1		0		0		-r+l/r-l  |
//\  |    0		  2/t-b		0		-t+b/t-b  |
//\  |	  0			0	 -2/f-n		-f+n/f-n  |
//\  |    0			0		0			1	  | 
//\=========================================================================
bool Matrix4::Orthographic(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar)
{
	float		deltaX = fRight - fLeft;
	float		deltaY = fTop - fBottom;
	float		deltaZ = fFar - fNear;

	// X-axis column
	m_11 = 2.0f / deltaX;	m_21 = 0.0f;	m_31 = 0.0f;	m_41 = 0.0f;
	// Y-axis column
	m_12 = 0.0f;	m_22 = 2.0f / deltaY;	m_32 = 0.0f;	m_42 = 0.0f;
	// Z-axis column
	m_13 = 0.0f;	m_23 = 0.0f;	m_33 = -2.0f / deltaZ;	m_43 = 0.0f;
	// Transpose column
	m_14 = -((fRight + fLeft) / deltaX);
	m_24 = -((fTop + fBottom) / deltaY);
	m_34 = -((fFar + fNear) / deltaZ);
	m_44 = 1.0f;

	return true;
}

//\=========================================================================
//\ Camera Projection Functions
//\ Sets view matrix following the right-handed (native) way:
//\  |	rx	ux	lx	-(r.e)	|	--> r = right vector
//\  |	ry	uy	ly	-(u.e)	|	--> u = up vector
//\  |	rz	uz	lz	-(l.e)	|	--> l = look vector
//\  |	0	0	0		1	|	--> e = eye vector
//\=========================================================================
Matrix4 Matrix4::LookAt(const Vector3& a_v3EyePos, const Vector3& a_v3Target, const Vector3& a_v3Up)
{
	Vector3 vRight;
	Vector3 vForward;
	Vector3 vUp;

	vForward = a_v3Target - a_v3EyePos;
	vForward.Normalize();

	vRight = Cross(vForward, a_v3Up);
	vRight.Normalize();
	vUp = Cross(vRight, vForward);
	vUp.Normalize();
	Matrix4 mat = Matrix4::IDENTITY;
	// X-axis column
	mat.m_11 = vRight.x; mat.m_21 = vRight.y; mat.m_31 = vRight.z; mat.m_41 = 0.0f;
	// Y-axis column
	mat.m_12 = vUp.x; mat.m_22 = vUp.y; mat.m_32 = vUp.z; mat.m_42 = 0.0f;
	// Z-axis column
	mat.m_13 = -vForward.x; mat.m_23 = -vForward.y; mat.m_33 = -vForward.z; mat.m_43 = 0.0f;
	mat.Transpose();
	mat.m_14 = -Dot(vRight, a_v3EyePos);
	mat.m_24 = -Dot(vUp, a_v3EyePos);;		// Two semi coloms?
	mat.m_34 = Dot(vForward, a_v3EyePos);;   // Two semi coloms?
	mat.m_44 = 1.0f;

	return mat;
}

//\ Orthonormalise
void Matrix4::Orthonormalise()
{
	Vector3 XBasis(m_11, m_21, m_31);					// Get current Right
	Vector3 YBasis(m_12, m_22, m_32);					// Get current Up
	Vector3 ZBasis(m_13, m_23, m_33);					// Get current Forward
	// Forward vector is the primary axis, so orthonormalise around this.
	YBasis = YBasis - (ZBasis * Dot(ZBasis, YBasis));	// Work out which Up should be derived from Forward
	YBasis.Normalize();									// Normalise the Up vector
	XBasis = Cross(YBasis, ZBasis);						// Get right vector for Up and Forward vectors
	XBasis.Normalize();									// To ensure vector is already normalised
	// Set the orthogonal vector axis back in to the matrix columns
	m_11 = XBasis.x; m_21 = XBasis.y; m_31 = XBasis.z;
	m_12 = YBasis.x; m_22 = YBasis.y; m_32 = YBasis.z;
	m_13 = ZBasis.x; m_23 = ZBasis.y; m_33 = ZBasis.z;
}

//\=========================================================================
//\ Shear Matrix
//\=========================================================================
void Matrix4::Shear(float xy, float xz, float yx, float yz, float zx, float zy)
{
	m_11 = 1.f;	m_12 = xy;	m_13 = xz;	m_14 = 0.f;
	m_21 = yx;	m_22 = 1.f;	m_23 = yz;	m_24 = 0.f;
	m_31 = zx;	m_32 = zy;	m_33 = 1.f;	m_34 = 0.f;
	m_41 = 0.f;	m_42 = 0.f;	m_43 = 0.f; m_44 = 1.f;
}