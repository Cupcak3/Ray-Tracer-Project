#include "mesh.h"
#include <fstream>
#include <string>
#include <limits>

// Consider a triangle to intersect a ray if the ray intersects the plane of the
// triangle with barycentric weights in [-weight_tolerance, 1+weight_tolerance]
static const double weight_tolerance = 1e-4;

// Read in a mesh from an obj file.  Populates the bounding box and registers
// one part per triangle (by setting number_parts).
void Mesh::Read_Obj(const char* file)
{
    std::ifstream fin(file);
    if(!fin)
    {
        exit(EXIT_FAILURE);
    }
    std::string line;
    ivec3 e;
    vec3 v;
    box.Make_Empty();
    while(fin)
    {
        getline(fin,line);

        if(sscanf(line.c_str(), "v %lg %lg %lg", &v[0], &v[1], &v[2]) == 3)
        {
            vertices.push_back(v);
            box.Include_Point(v);
        }

        if(sscanf(line.c_str(), "f %d %d %d", &e[0], &e[1], &e[2]) == 3)
        {
            for(int i=0;i<3;i++) e[i]--;
            triangles.push_back(e);
        }
    }
    number_parts=triangles.size();
}

// Check for an intersection against the ray.  See the base class for details.
Hit Mesh::Intersection(const Ray& ray, int part) const
{
    //TODO;
	//if intersect triangles[part]
	//	calculate
	//  return
	double t;
	
	if (part >= 0) //test only that part
	{
		if (Intersect_Triangle(ray, part, t))
		{
			return {this, t, part};
		}
	}
	else          //test all parts
	{
		for (int i = 0; i < triangles.size(); ++i)
		{
			if (Intersect_Triangle(ray, i, t))
			{
				return {this, t, i};
			}
		}
	}
	
    return {NULL,0,0};
}

// Compute the normal direction for the triangle with index part.
vec3 Mesh::Normal(const vec3& point, int part) const
{
    assert(part>=0);
    //TODO;
	vec3 v1 = vertices[triangles[part][1]] - point;
	vec3 v2 = vertices[triangles[part][2]] - point;
	
    return cross(v1, v2);
}

static double Calc_Area(const vec3 &A, const vec3 &B, const vec3 &C)
{
	return abs((A[0] * (B[1]-C[1]) + B[0] * (C[1] - A[1]) + C[0] * (A[1] - B[1]))/(2));
}

// This is a helper routine whose purpose is to simplify the implementation
// of the Intersection routine.  It should test for an intersection between
// the ray and the triangle with index tri.  If an intersection exists,
// record the distance and return true.  Otherwise, return false.
// This intersection should be computed by determining the intersection of
// the ray and the plane of the triangle.  From this, determine (1) where
// along the ray the intersection point occurs (dist) and (2) the barycentric
// coordinates within the triangle where the intersection occurs.  The
// triangle intersects the ray if dist>small_t and the barycentric weights are
// larger than -weight_tolerance.  The use of small_t avoid the self-shadowing
// bug, and the use of weight_tolerance prevents rays from passing in between
// two triangles.
bool Mesh::Intersect_Triangle(const Ray& ray, int tri, double& dist) const
{
    //TODO;
	vec3 A = vertices[triangles[tri][0]];
	vec3 B = vertices[triangles[tri][1]];
	vec3 C = vertices[triangles[tri][2]];
	
	vec3 normal = Mesh::Normal(A, tri);
	
	Plane plane = Plane(A, normal);
	Hit hit = {NULL,0,0};
	hit = plane.Intersection(ray, -1);
	if (hit.object && hit.dist > small_t)
	{
		// intersects triangle's plane
		
		vec3 P = ray.Point(hit.dist);
		
		double Triangle_Area = Calc_Area(A, B, C);
		double alpha, beta, gamma, A_a, A_b, A_c;
		
		A_a = Calc_Area(P, B, C);
		A_b = Calc_Area(P, A, C);
		A_c = Calc_Area(P, A, B);
		
		alpha = A_a / Triangle_Area;
		beta  = A_b / Triangle_Area;
		gamma = A_c / Triangle_Area;
		
		if ((alpha + beta + gamma) == 1 && (alpha > -weight_tol) && (beta > -weight_tol) && (gamma > -weight_tol))
		{
			dist = hit.dist;
			return true;
		}
		
	}
    return false;
}

// Compute the bounding box.  Return the bounding box of only the triangle whose
// index is part.
Box Mesh::Bounding_Box(int part) const
{
    Box b;
    TODO;
    return b;
}
