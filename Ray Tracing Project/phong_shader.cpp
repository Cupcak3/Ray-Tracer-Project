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
	// color = R_a * L_a + R_d * L_d * max(dot(normal, lightvec), 0) + R_s * L_s * max(dot(v, reflection)^a;
	// R_<type>   = color_<type>; L = light->emitted_light(Point_to_Light);
	// lightvec   = light to point/intersection ray; v = point/intersection to viewer direction
	// reflection = Light reflection direction
	
	vec3 ambient_intensity, diffuse_intensity, specular_intensity = {0,0,0};
	ambient_intensity = color_ambient * world.ambient_color * world.ambient_intensity;
	for (Light* light : world.lights)
	{
		vec3 Light_Direction = light->position-intersection_point;
		vec3 Light_Produced = light->Emitted_Light(Light_Direction);
		vec3 reflection = (2 * dot(normal,Light_Direction.normalized()) * normal - Light_Direction.normalized()).normalized();
		vec3 v = -(ray.direction).normalized();

		Ray shadow_ray;
		shadow_ray.endpoint = intersection_point;
		shadow_ray.direction = Light_Direction;
		Hit hit = world.Closest_Intersection(shadow_ray);
		for (Object *object: world.objects)
		{
			if (!object->Intersection(shadow_ray, -1).object) {
				//diffuse_intensity +=  color_diffuse  * Light_Produced * fmax(dot(normal, Light_Direction.normalized()), 0.0);
				//specular_intensity += color_specular * Light_Produced * pow(fmax(dot(v, reflection), 0.0), specular_power);
			}
			else{
				//hit an object
				//std::cout<<"Ray at "<<intersection_point<<" hit object "<<hit.object<<std::endl;
			}
		}
		diffuse_intensity +=  color_diffuse  * Light_Produced * fmax(dot(normal, Light_Direction.normalized()), 0.0);
		specular_intensity += color_specular * Light_Produced * pow(fmax(dot(v, reflection), 0.0), specular_power);
	}
	color = ambient_intensity + diffuse_intensity + specular_intensity;
	if(debug_pixel)
	{
		std::cout<<"call Shade_Surface with location = "<<intersection_point<<"; normal = "<<normal<<std::endl<<"ambient = "<<color_ambient<<std::endl;
		std::cout<<"shading for light: diffuse = "<<diffuse_intensity<<"; specular = "<<specular_intensity<<std::endl<<"final color "<<color<<std::endl;
	}
	return color;
}
