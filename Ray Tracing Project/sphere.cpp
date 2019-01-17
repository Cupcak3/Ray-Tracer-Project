#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    //TODO;
	// sphere (X - C) * (X - C) = r^2
	// (E + Ut - C) * (E + Ut - C) = r^2
	// t = (- b +/- sqrt(b^2-4ac) ) ÷ (2a)
	
	vec3 ray_to_sphere_center = ray.endpoint - this->center;
	
	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.direction, ray_to_sphere_center);
	float c = dot(ray_to_sphere_center, ray_to_sphere_center) - pow(radius, 2.0);
	
	float t;
	if (pow(b, 2.0)- 4 * a * c < 0 || pow(b, 2.0)- 4 * a * c == 0) {
		return {0,0,0}; // No intersection
	}
	else {
		float t_1 = (-b + sqrt(pow(b, 2.0) - 4 * a * c)) / (2.0 * a);
		float t_2 = (-b - sqrt(pow(b, 2.0) - 4 * a * c)) / (2.0 * a);
		// Determine which is first in ray starting from endpoint
		t = ((ray.Point(t_1)-ray.endpoint).magnitude() < (ray.Point(t_2)-ray.endpoint).magnitude()) && (t_1 > 0)  ? t_1 : t_2;
	}
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
