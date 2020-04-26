#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class sphere : public hitable {
	public:
		vec3 center;
		float radius;
		material *mat_ptr;
		
		sphere() {}
		sphere(vec3 cen,float r) : center(cen), radius(r) {}
		sphere(vec3 cen,float r,material *mat_ptr) : center(cen), radius(r), mat_ptr(mat_ptr) {}
		
		virtual bool hit(const ray &r,float tmin,float tmax,hit_record &rec) const;
		virtual bool bounding_box(float t0,float t1,aabb &output_box) const;
};

bool sphere::hit(const ray &r,float tmin,float tmax,hit_record &rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if(discriminant > 0) {
		float t = (-b - sqrt(discriminant)) / (2.0 * a);
		if(t < tmax && t > tmin) {
			rec.t = t, rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if(t < tmax && t > tmin) {
			rec.t = t, rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

bool sphere::bounding_box(float t0,float t1,aabb &output_box) const {
	output_box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
	return true;
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while(p.squared_length() >= 1.0);
	return p;
}
#endif
