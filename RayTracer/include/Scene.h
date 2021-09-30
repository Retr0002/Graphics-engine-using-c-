#pragma once

#include <vector>
#include <libMath.h>
//#include "IntersectionResponse.h"

struct IntersectResponse;
class Primitive;
class Camera;
class Light;


class Scene
{
public:
	Scene();														// Constructor
	~Scene();														// Destsructor

	void AddObject(const Primitive* a_object);						// Adds an object to the scene
	void RemoveObject(const Primitive* a_object);					// Removes an object from the scene

	void AddLight(const Light* a_light);
	void RemoveLight(const Light* a_light);
	
	Vector3 CastRay(const Vector2& a_screenSpacePos) const;
	bool IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const;	// Checks if a ray intersects with an object

	void SetCamera(Camera* a_pCamera) { m_pCamera = a_pCamera; }

private:
	std::vector<const Primitive*> m_objects;
	std::vector<const Light*> m_lights;
	Camera* m_pCamera;
};