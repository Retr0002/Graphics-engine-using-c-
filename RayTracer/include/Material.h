#pragma once

#include <libMath.h>

//\======================================================================================
//\ An abstract base material class
//\======================================================================================
class Material
{
public:
	Material() : m_albedo(1.f, 1.f, 1.f), m_ambient(0.f), m_diffuse(0.f), m_specular(0.f), m_roughness(0.f) {};
	Material(const Vector3& a_albedo, float a_ambient, float a_diffuse, float a_specular, float a_roughness) :
		m_albedo(a_albedo), m_ambient(a_ambient), m_diffuse(a_diffuse), m_specular(a_specular), m_roughness(a_roughness) {};
	~Material() {};

	const Vector3& GetAlbedo() { return m_albedo; }
	void SetAlbedo(const Vector3& a_albedo) { m_albedo; }

	const float& GetAmbient() const { return m_ambient; }
	void SetAmbient(const float& a_ambient) { m_ambient = a_ambient; }

	const float& GetDiffuse() const { return m_diffuse; }
	void SetDiffuse(const float& a_diffuse) { m_diffuse = a_diffuse; }

	const float& GetSpecular() const { return m_specular; }
	void SetSpecular(const float& a_specular) { m_specular = a_specular; }

	const float& GetRoughness() const { return m_roughness; }
	void SetRoughness(const float& a_roughness) { m_roughness = a_roughness; }

protected:
	Vector3 m_albedo;		// Material albedo colour - colour of light reflected from surface
	float m_ambient;		// Ambient component of material 0 -> 1.0
	float m_diffuse;		// Diffuse component of material 0 -> 1.0
	float m_specular;		// Specular component of material 0 -> 1.0
	float m_roughness;		// Surface roughness of material 0 -> 1.0
};
