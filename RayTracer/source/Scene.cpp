#include "Scene.h"
#include "Primitive.h"
#include "Camera.h"
#include "Light.h"
#include "IntersectionResponse.h"

Scene::Scene() : m_pCamera(nullptr)
{
	m_objects.clear();
	m_lights.clear();
}

Scene:: ~Scene()
{
	m_pCamera = nullptr;
	m_objects.clear();
	m_lights.clear();
}

void Scene::AddObject(const Primitive* a_object)
{
	m_objects.push_back(a_object);
}

void Scene::RemoveObject(const Primitive* a_object)
{
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if (*iter == a_object)				// We have found an object
		{
			iter = m_objects.erase(iter);	// Delete the object from the vector
		}
	}
}

void Scene::AddLight(const Light* a_light)
{
	m_lights.push_back(a_light);
}

void Scene::RemoveLight(const Light* a_light)
{
	for (auto iter = m_lights.begin(); iter != m_lights.end(); ++iter)
	{
		if (*iter == a_light)				// We have found the light
		{
			iter = m_lights.erase(iter);
		}
	}
}

Vector3 Scene::CastRay(const Vector2& a_screenSpacePos) const
{
	// Create a ray with origin at the camera and direction into the near place offset
	Ray viewRay = m_pCamera->CastRay(a_screenSpacePos);
	// Convert ray direction into colour space 0->1

	IntersectResponse ir;
	//if there is an intersection we calculate the lighting and the effect all lights in the scene have on the object
	//we then call a test to see if we have intersected with an object and return the colour of the ray
	if (IntersectTest(viewRay, ir))								// If there is an intersection
	{
		Vector3 rayColour = Vector3(0.f, 0.f, 0.f);				// Calculate lighting
		// Calculate the effect all lights in the scene have on the object
		for (auto lightIter = m_lights.begin(); lightIter != m_lights.end(); ++lightIter)
		{
			// Test to see if in shadow
			Ray shadowRay = Ray(ir.HitPos, -(*lightIter)->GetDirectionToLight(ir.HitPos), 0.001f);
			IntersectResponse sr;
			float shadowValue = (!IntersectTest(shadowRay, sr));	//Call HitTest on the shadow ray to see if we have an occluder
			rayColour += (*lightIter)->CalculateLighting(ir, m_pCamera->GetPosition()) * shadowValue;
		}
		return rayColour;
	}
	else
	{
		Vector3 rayToColour = RayToColour(viewRay);
		// Use LERP to get a colour between white and blue based on the vertical value of the rayColour
		rayToColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayToColour.y);
		return rayToColour;
	}
}

bool Scene::IntersectTest(const Ray& a_ray, IntersectResponse& a_ir) const
{
	// Set the current hit distance to be far away
	float intersectDist = a_ray.MaxDistance();								// This is the maximum value that a float can hold
	bool intersectionOccured = false;
	IntersectResponse objectIntersection;
	// Test each object in the world to see if the ray intersects
	for (auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		const Primitive* object = (*iter);						// Get a pointer to the primitive object
		if (object->IntersectTest(a_ray, objectIntersection))	// An intersection occured
		{
			if (objectIntersection.distance > a_ray.MinLength())
			{
				intersectionOccured = true;
				if (objectIntersection.distance < intersectDist)	// Is this intersection closer?
				{
					intersectDist = objectIntersection.distance;	// Store the new disstance
					a_ir = objectIntersection;						// Copy the data from the intersection response
				}
			}
		}
	}
	return intersectionOccured;
}