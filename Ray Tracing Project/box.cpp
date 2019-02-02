#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersection(const Ray& ray) const
{
    //TODO;
	double tmin = -std::numeric_limits<double>::infinity();
	double tmax = -tmin;
	
	for (int i = 0; i < 3; ++i)
	{
		if ((ray.direction[i]) == 0 && (ray.endpoint[i] < std::min(lo[i], hi[i])) && (ray.endpoint[i] > std::max(lo[i], hi[i])))
		{
			return false;
		}
		else
		{
			double tmin_temp = (std::min(lo[i],hi[i])-ray.endpoint[i]) / ray.direction[i];
			double tmax_temp = (std::max(lo[i],hi[i])-ray.endpoint[i]) / ray.direction[i];
			
			if (tmin_temp > tmax_temp) std::swap(tmin_temp, tmax_temp);
			
			tmin = std::min(tmin, tmin_temp);
			tmax = std::max(tmax, tmax_temp);
			
			if (tmin > tmax || tmax < 0) {
				return false;
			}
		}
	}
	
    return true;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
	// TODO;
    Box box;
	box.lo = this->lo;
	box.hi = this->hi;
	
	for (int i = 0; i < 3; ++i)
	{
		box.lo[i] = std::min(this->lo[i], bb.lo[i]);
		box.hi[i] = std::max(this->hi[i], bb.hi[i]);
	} // Simple expansion by each coordinate, not sure if this is fool proof
	// Actually this was given by componentwise_max and componentwise_min
	// but I didn't know that at the time of writing the algorithm
	
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    // TODO;
	if (lo[0] == std::numeric_limits<double>::infinity()) {
		lo = hi = pt;
		return;
	}
	
	bool good_x, good_y, good_z;
	
	good_x = (lo[0] <= pt[0] && pt[0] <= hi[0]);
	good_y = (lo[1] <= pt[1] && pt[1] <= hi[1]);
	good_z = (lo[2] <= pt[2] && pt[2] <= hi[2]);
	
	if (!(good_x && good_y && good_z))
	{
		//find smallest box with point and current box
		Box b;
		b.lo = b.hi = pt;
		b = this->Union(b);
		this->lo = b.lo;
		this->hi = b.hi;
	}
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}
