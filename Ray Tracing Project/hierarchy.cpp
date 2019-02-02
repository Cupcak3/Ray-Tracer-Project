#include <algorithm>
#include "hierarchy.h"

// Reorder the entries vector so that adjacent entries tend to be nearby.
// You may want to implement box.cpp first.
void Hierarchy::Reorder_Entries()
{
    if(!entries.size()) return;
    TODO;
	for (Entry entry : entries)
	{
		
	}
	//std::cout<<"Reordered entires"<<std::endl;
}

// Populate tree from entries.
void Hierarchy::Build_Tree()
{
    if(!entries.size()) return;
	// TODO;
	for (int i = 0; i < entries.size(); ++i)
	{
		tree.push_back(entries[i].box);
	}
	//std::cout<<"Built tree"<<std::endl;
}

// Return a list of candidates (indices into the entries list) whose
// bounding boxes intersect the ray.
void Hierarchy::Intersection_Candidates(const Ray& ray, std::vector<int>& candidates) const
{
    // TODO;
	for(int i = 0; i < entries.size(); ++i)
	{
		if (entries[i].box.Intersection(ray)) candidates.push_back(i);
	}
}
