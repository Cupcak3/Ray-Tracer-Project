#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
	float r,g,b;
	r = color[0];
	g = color[1];
	b = color[2];
	
    TODO; //determine the color
	//color += color_diffuse;
	// RdLd*max(n*L,0)
	for (Light* light : world.lights)
	{
		color += color_diffuse*dot(normal, (light->position-intersection_point).normalized());
	}
	
	//color = color_diffuse*fmax(dot(normal, ray.direction),0);
    return color;
}
