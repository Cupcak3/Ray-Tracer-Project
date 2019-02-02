#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
	// TODO; I'm going to leave these in and commented so that I can easily tell which functions I edit
	float min_t = std::numeric_limits<float>::max();
	Hit closest_hit = {NULL,0,0}; // I think this is what object.h is requiring. Initialized null so that only intersections are recorded
	/*for (Object* object: objects)
	{
		Hit hit = object->Intersection(ray, -1);  // Not sure what the part attribute/argument is for yet but I assume -1 is ok for now as per documentation. Probably changes later
		if (hit.object && hit.dist < min_t && hit.dist >= small_t)
		{
			min_t = hit.dist;  // Update min_t. Ensures closest object to camera is registered.
			closest_hit = hit; // Register the new closest object intersection
		}
	}*/
	std::vector<int> candidates;
	hierarchy.Intersection_Candidates(ray, candidates);
	for (int i : candidates)
	{
		Hit hit = hierarchy.entries.at(i).obj->Intersection(ray, hierarchy.entries.at(i).part);
		if (hit.object && hit.dist < min_t && hit.dist >= small_t)
		{
			min_t = hit.dist;
			closest_hit = hit;
		}
	}
	if (debug_pixel)
	{
		std::cout<<"closest intersection: obj = "<<&closest_hit.object<<"; part = "<<closest_hit.part<<"; dist = "<<closest_hit.dist<<std::endl;
	}
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
	// set up the initial view ray here
	// TODO;
    Ray ray;
	ray.endpoint = camera.position;
	ray.direction = (camera.World_Position(pixel_index)-ray.endpoint).normalized(); // Normalize view ray from endpoint --> pixel point
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
	// determine the color here;
	//TODO;
	
	if(debug_pixel)
	{
		std::cout<<"cast ray: end = "<<ray.endpoint<<"; dir = "<<ray.direction<<std::endl;
	}
	
	Hit hit = Closest_Intersection(ray);
	if (hit.object && recursion_depth <= recursion_depth_limit) // checks against NULL. if there is an intersection hit.object is non-NULL
	{
		color = hit.object->material_shader->Shade_Surface(ray, ray.Point(hit.dist), hit.object->Normal(ray.Point(hit.dist), hit.part), recursion_depth); // Shade the object
	}
	else
	{
		vec3 dummy = {0,0,0};
		color = this->background_shader->Shade_Surface(ray, dummy, dummy, recursion_depth); //Background is whatever the shader says
	}

    return color;
}

void Render_World::Initialize_Hierarchy()
{
    // TODO;
	// Fill in hierarchy.entries; there should be one entry for
    // each part of each object.
	for (Object* object : objects)
	{
		for (int part = 0; part < object->number_parts; ++part)
		{
			Entry entry = {object, part, object->Bounding_Box(part)};
			hierarchy.entries.push_back(entry);
		}
	}

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
