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
	
    TODO; //determine the color
	
	vec3 ambient_intensity, diffuse_intensity, specular_intensity = {0,0,0};
	// vec3 k_a = ambient_reflection constant
	// vec3 i_a = ambient_reflection intensity (color?)
	// color = k_a*i_a;
	for (Light* light : world.lights)
	{
		//color += (k_d*(L_m*N)*i_m_d + k_s*(R_m*V)^(a)*i_m_s)
		//vec3 k_d = diffuse reflection constant (lambertian reflectance)
		//vec3 L_m = direction vector from point on surface towards each light source (light)
		//vec3 N = normal at point on surface
		//vec3 i_m_d = intensity of diffuse component of light source (light)
		//vec3 k_s = specular reflection constant
		//vec3 R_m = reflection of L_m = 2 (L_m*N)*N-L_m
		//vec3 v = direction pointing towards viewer = -ray.direction
		//double a = shiniess constant = specular_power
		//vec3 i_m_s = intensity of specular component of light source (light)
		//vec3 ambient_intensity, diffuse_intensity, specular_intensity;
		
		diffuse_intensity += light->Emitted_Light(light->position-intersection_point) * color_diffuse * fmax(dot((light->position-intersection_point).normalized(), normal),0.0);
	}
	color = diffuse_intensity /* + specular_intensity */;
	//std::cout<<"Using phong shading"<<std::endl;
	//color = color_diffuse*fmax(dot(normal, ray.direction),0);
    return color;
}
