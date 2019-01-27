#include "plane.h"
#include "ray.h"
#include <cfloat>
#include <limits>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
	//TODO;
	// ((E-Q) + tU)*N=0
	// (E-Q)N + t*U*N=0
	// t*U*N = -((E-Q)N)
	// t = ((Q-E)*N) ÷ (U*N)
	float denominator = dot(ray.direction, this->normal);
	if (denominator != 0)
	{
		float t = dot(this->x1-ray.endpoint, this->normal) / denominator;
		if (t > small_t)
		{
			return {this, t, -1}; //-1 MAY HAVE TO CHANGE LATER
		}
	}
    return {NULL,0,0}; // No intersection
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
