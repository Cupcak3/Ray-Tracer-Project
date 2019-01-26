#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    // TODO; // determine the color
	color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

	// compute reflected ray r = view/light - 2 * dot(light/view, normal) * normal
	if (recursion_depth <= world.recursion_depth_limit)
	{
		Ray Reflection_Ray = {intersection_point, (ray.direction - 2 * dot(ray.direction, normal) * normal).normalized()};
		// color = (1-k) * color + k * cast_ray(reflected ray)
		// k = reflectivity
		color = (1-this->reflectivity) * color + this->reflectivity * world.Cast_Ray(Reflection_Ray, ++recursion_depth);
	}
    return color;
}
