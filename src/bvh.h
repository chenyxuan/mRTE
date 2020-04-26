#ifndef BVH_H
#define BVH_H

#include <cstdio>
#include <algorithm>
#include <cassert>
#include "aabb.h"
#include "ray.h"
#include "hitablelist.h"

class bvh_node : public hitable {
	public:
		hitable_list list;
		bool is_leaf;
		bvh_node *left;
		bvh_node *right;
		aabb box;
		
		bvh_node() {}
		bvh_node(hitable_list &list);
		
		virtual bool hit(const ray &r,float tmin,float tmax,hit_record &rec) const;
		virtual bool bounding_box(float t0,float t1,aabb &output_box) const;
};

bool bvh_node::bounding_box(float t0,float t1,aabb &output_box) const {
	output_box = box;
	return true;
}

bool bvh_node::hit(const ray &r,float tmin,float tmax,hit_record &rec) const {
	if(!box.hit(r, tmin, tmax)) return false;
	
	if(is_leaf) {
		return list.hit(r, tmin, tmax, rec);
	} else {
		bool hit_left = left->hit(r, tmin, tmax, rec);
		bool hit_right = right->hit(r, tmin, hit_left ? rec.t : tmax, rec);
		return hit_left || hit_right;
	}
}
inline bool box_compare(const hitable *a,const hitable *b,int axis) {
	static aabb box_a, box_b;
	if(!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b)) {
		fprintf(stderr, "No bounding box in bvh_node constructor.\n");
	}
	return box_a.max().e[axis] < box_b.max().e[axis];
}
inline bool box_x_compare(const hitable *a,const hitable *b) {
	return box_compare(a, b, 0);
}
inline bool box_y_compare(const hitable *a,const hitable *b) {
	return box_compare(a, b, 1);
}
inline bool box_z_compare(const hitable *a,const hitable *b) {
	return box_compare(a, b, 2);
}

static bool (*comparator_array[3])(const hitable *,const hitable *) = {box_x_compare, box_y_compare, box_z_compare};

bvh_node::bvh_node(hitable_list &list) : list(list) {
	bool (*comparator)(const hitable *,const hitable *) = comparator_array[1];
	
	if(list.list_size <= 300) {
		is_leaf = true;
		left = right = NULL;
		assert(list.bounding_box(0, 0, box));
	} else {
		is_leaf = false;
		std::sort(list.list, list.list + list.list_size, comparator);
		int mid = list.list_size / 2;
		hitable_list left_list(list.list, mid);
		hitable_list right_list(list.list + mid, list.list_size - mid);
		left = new bvh_node(left_list);
		right = new bvh_node(right_list);
		box = surrounding_box(left->box, right->box);
	}
}
#endif
