#include "DirectionalLight.h"
#include "MathUtil.h"
#include "Vector3.h"
#include <cmath>
#include "IntersectionResponse.h"
#include "Material.h"

DirectionalLight::DirectionalLight()
{
	SetDirection(Vector3(0.f, 0.f, 0.f));
}

DirectionalLight::DirectionalLight(const Matrix4& a_transform, const Vector3& a_colour, const Vector3& a_facing)
	: Light(a_transform, a_colour)
{
	SetDirection(a_facing);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirection(const Vector3& a_direction, const Vector3& a_up)
{
	m_Transform.SetColumn(2, a_direction);
	m_Transform.SetColumn(1, a_up);
	m_Transform.Orthonormalise();
}

Vector3 DirectionalLight::GetDirection() const
{
	return m_Transform.GetColumn(2).xyz();
}

ColourRGB DirectionalLight::CalculateLighting(const IntersectResponse& a_ir, const Vector3& a_eyePos, float a_shadowFactor) const
{
	//Calculate effective light colour for diffuse channel (and metallic specular)
	Vector3 effectiveColour = m_colourRGB * a_ir.material->GetAlbedo();

	ColourRGB ambient = effectiveColour * a_ir.material->GetAmbient();			//Get ambient colour for surface
	//Light direction is forward axis of light matrix
	Vector3 lightDirection = -GetDirection();									//Get direction to light from surface WAS "Vector3 lightDirection = -this->GetDirection();"
	float lightDiffuse = MathUtil::Max(0.f, Dot(lightDirection, a_ir.SurfaceNormal));	//Positive values indicate vectors in same dir
	ColourRGB diffuse = effectiveColour * a_ir.material->GetDiffuse() * lightDiffuse;	//Blend light diffuse with diffuse value and colour
	//Calculate light specular value
	Vector3 eyeDir = Normalize(a_ir.HitPos - a_eyePos);							//Get the dir from view to surface
	Vector3 reflectionVec = Reflect(eyeDir,a_ir.SurfaceNormal);					//Get the reflection vector of the eye around normal
	//Specular power indicates roughness of the surface material use roughness to control specular power as a range betweeen 0_> 255
	float specularPower = (1.0f - a_ir.material->GetRoughness()) * 254.f + 1.0;
	float specularFactor = std::powf(MathUtil::Max(0.f, Dot(reflectionVec, lightDirection)), specularPower);//Get the specular value
	ColourRGB specular = m_colourRGB * a_ir.material->GetSpecular() * specularFactor;

	return ambient + ((diffuse + specular) * a_shadowFactor);
}

Vector3 DirectionalLight::GetDirectionToLight(const Vector3& a_point) const
{
	return GetDirection();
}