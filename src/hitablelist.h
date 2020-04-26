#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class hitable_list : public hitable {
	public:
		int list_size;
		hitable **list;
		
		hitable_list() { list_size = 0, list = NULL; }
		hitable_list(hitable **l,int n) : list(l), list_size(n) {}
		
		virtual bool hit(const ray &r,float tmin,float tmax,hit_record &rec) const;
		virtual bool bounding_box(float t0,float t1,aabb &output_box) const;
};

bool hitable_list::hit(const ray &r,float tmin,float tmax,hit_record &rec) const {
	hit_record temp;
	bool hit = false;
	float tcur = tmax;
	
	for(int i = 0; i < list_size; i++) {
		if(list[i]->hit(r, tmin, tcur, temp)) {
			hit = true;
			tcur = temp.t;
			rec = temp;
		}
	}
	
	return hit;
}

bool hitable_list::bounding_box(float t0,float t1,aabb &output_box) const {
	if(list_size == 0) return false;
	
	aabb temp_box;
	bool first_box = true;
	
	for(int i = 0; i < list_size; i++) {
		if(!list[i]->bounding_box(t0, t1, temp_box)) return false;
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}
	
	return true;
}
#endif
