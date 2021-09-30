#pragma once
#include <libMath.h>
#include "ColourRGB.h"

struct IntersectResponse;

class Light
{
public:
	Light();
	Light(const Matrix4& a_transform, const ColourRGB& a_colour);  //(const Matrix4& a_tranform...) ?*****
	virtual ~Light();
	//Each type of light will need to calculate it's own lighting outcome based off the type of light it is
	virtual ColourRGB CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor = 1.0) const = 0;
	//We will need to have a function to get the direction to the light from a given point
	virtual Vector3 GetDirectionToLight(const Vector3& a_point = Vector3(0.f, 0.f, 0.f)) const;
	//Get and set Lights matrix
	Matrix4 GetTransform() const;
	void SetTransform(const Matrix4& a_m4);
	//Get and Set the position of the light
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& a_v3);
	//Set and Get the colour of the light -- implemented in header as it's so straight forward
	const ColourRGB& GetColour() const { return m_colourRGB; }
	void SetColour(const ColourRGB& a_colour) { m_colourRGB = a_colour; }


protected:
	Matrix4 m_Transform;		//Transform of the light
	ColourRGB m_colourRGB;		//Colour of the light

};