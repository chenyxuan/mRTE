#ifndef RAYH
#define RAYH
#include "vec3.h"

struct ray {
	vec3 a, b;
	
	ray(const vec3 &a,const vec3 &b):a(a), b(b) {}
	
	vec3 origin() const { return a; }
	vec3 direction() const { return b; }
	vec3 point_at_parameter(float t) const { return a + t * b; }
};

#endif
