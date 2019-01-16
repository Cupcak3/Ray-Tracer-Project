#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
	vec3 ray_to_sphere_center = ray.endpoint - this->center;
	
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, ray_to_sphere_center);
	float c = dot(ray_to_sphere_center, ray_to_sphere_center) - pow(radius, 2.0);
	
	
	if (pow(b, 2.0)- 4 * a * c < 0) {
		return {0,0,0}; // No intersection
	}
	float t = (-b - sqrt(pow(b, 2.0) - 4 * a * c < 0)) / (2.0 * a);
	return {this, t, -1}; //-1 MAY HAVE TO CHANGE LATER
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
