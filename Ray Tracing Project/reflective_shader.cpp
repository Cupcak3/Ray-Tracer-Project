#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    TODO; // determine the color
	color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
	//color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
	// compute reflected ray r = view/light - 2 * dot(normal, light/view) * normal
	if (recursion_depth < world.recursion_depth_limit)
	{
		Ray reflection;
		reflection.direction = (ray.direction - 2 * dot(ray.direction, normal.normalized()) * normal.normalized());
		reflection.endpoint = intersection_point + reflection.direction*small_t;
		// color = (1-k) * color + k * cast_ray(reflected ray)
		// k = reflectivity
	
		color += (1-reflectivity) * color + reflectivity * world.Cast_Ray(reflection, ++recursion_depth);
	}
    return color;
}
