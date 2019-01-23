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
	
	//TODO; //determine the color
	//color = R_a*L_a +R_d*L_dmax(dot(normal,lightvec),0)+R_s*L_s*max(dot(v,reflection)^a;
	//R = color_<type>; L = light->emitted_light();
	
	vec3 ambient_intensity, diffuse_intensity, specular_intensity = {0,0,0};
	// vec3 k_a = ambient_reflection constant
	// vec3 i_a = ambient_reflection intensity (color?)
	// ambient_intensity = color_ambient;
	for (Light* light : world.lights)
	{
		//color += (k_d*i_m_d*(L_m*N) + k_s*i_m_s*(R_m*V)^(a))
		//vec3 k_d = diffuse reflection constant (lambertian reflectance)
		//vec3 L_m = direction vector from point on surface towards each light source (light)
		vec3 Point_to_Light = light->position-intersection_point;
		//vec3 N = normal at point on surface
		//vec3 i_m_d = intensity of diffuse component of light source (light)
		//vec3 k_s = specular reflection constant
		vec3 Reflected_Direction = (2 * dot(normal,Point_to_Light.normalized()) * normal - Point_to_Light.normalized()).normalized() ; //reflection of L_m
		//vec3 v = direction pointing towards viewer = -ray.direction
		vec3 V = (ray.endpoint-intersection_point).normalized();
		//double a = shiniess constant = specular_power
		//vec3 i_m_s = intensity of specular component of light source (light)
		
		diffuse_intensity +=  color_diffuse * light->Emitted_Light(Point_to_Light) * fmax(dot(normal, Point_to_Light.normalized()),0.0);
		specular_intensity += color_specular * light->Emitted_Light(Point_to_Light) * pow(fmax(dot(V, Reflected_Direction), 0.0),specular_power);
		
	}
	color = ambient_intensity + diffuse_intensity + specular_intensity;
	if(debug_pixel)
	{
		std::cout<<"call Shade_Surface with location = "<< intersection_point<<"; normal = "<<normal<<std::endl<<"ambient = "<<color_ambient<<std::endl;
		std::cout<<"shading for light: diffuse = "<<diffuse_intensity<<"; specular = "<<specular_intensity<<std::endl<<"final color "<<color<<std::endl;
	}
	return color;
}
