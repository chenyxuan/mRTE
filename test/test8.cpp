#include <cstdio>
#include "../src/sphere.h"
#include "../src/hitablelist.h"
#include "../src/scamera.h"

vec3 color(const ray &r,hitable_list *world) {
	hit_record rec;
	if(world->hit(r, 0.0, MAXFLOAT, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(ray(rec.p, target - rec.p), world);
	} else {
		vec3 unit_direction = r.direction().unit_vector();
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main() {
	int nx = 200;
	int ny = 100;
	int ns = 100;
	printf("P3\n%d %d\n255\n", nx, ny);
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable_list *world = new hitable_list(list, 2);
	camera cam;
	
	for(int j = ny - 1; j >= 0; j--)
		for(int i = 0; i < nx; i++) {
			vec3 col(0.0, 0.0, 0.0);
			for(int s = 0; s < ns; s++) {
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world);
			}
			col /= ns;
			
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			printf("%d %d %d\n", ir, ig, ib);
		}
	
	return 0;
}
