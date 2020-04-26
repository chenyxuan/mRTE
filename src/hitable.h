#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "aabb.h"

class material;

struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

class hitable {
	public:
		virtual bool hit(const ray &r,float tmin,float tmax, hit_record &rec) const = 0;
		virtual bool bounding_box(float t0,float t1,aabb &output_box) const = 0;
};

#endif
