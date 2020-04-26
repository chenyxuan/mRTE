#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable {
	public:
		int list_size;
		hitable **list;
		
		hitable_list() {}
		hitable_list(hitable **l,int n) : list(l), list_size(n) {}
		
		virtual bool hit(const ray &r,float tmin,float tmax,hit_record &rec) const;
};

bool hitable_list::hit(const ray &r,float tmin,float tmax,hit_record &rec) const {
	hit_record temp;
	bool hit = false;
	double tcur = tmax;
	
	for(int i = 0; i < list_size; i++) {
		if(list[i]->hit(r, tmin, tcur, temp)) {
			hit = true;
			tcur = temp.t;
			rec = temp;
		}
	}
	
	return hit;
}
#endif
