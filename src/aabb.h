#ifndef AABB_H
#define AABB_H

#include <cmath>
#include "ray.h"

class aabb {
	public:
		vec3 _min;
		vec3 _max;
		
		aabb() {}
		aabb(const vec3 &a,const vec3 &b) : _min(a), _max(b) {}
		
		vec3 min() const { return _min; }
		vec3 max() const { return _max; }
		
		inline bool hit(const ray &r,float tmin,float tmax) const {
			for(int a = 0; a < 3; a++) {
				float t0 = fminf((_min[a] - r.origin()[a]) / r.direction()[a],
								(_max[a] - r.origin()[a]) / r.direction()[a]);
				float t1 = fmaxf((_min[a] - r.origin()[a]) / r.direction()[a],
								(_max[a] - r.origin()[a]) / r.direction()[a]);
				tmin = fmaxf(tmin, t0);
				tmax = fmaxf(tmax, t1);
				if(tmax <= tmin) return false;
			}
			return true;
		}
};

inline aabb surrounding_box(const aabb &box0,const aabb &box1) {
	vec3 min(vec3(fminf(box0.min().x(), box1.min().x()),
				fminf(box0.min().y(), box1.min().y()),
				fminf(box0.min().z(), box1.min().z())));
	vec3 max(vec3(fminf(box0.max().x(), box1.max().x()),
				fminf(box0.max().y(), box1.max().y()),
				fminf(box0.max().z(), box1.max().z())));
	return aabb(min, max);
}
#endif
