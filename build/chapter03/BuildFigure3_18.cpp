#include "World/World.h"

void World::build() {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);

	background_color = black;
	tracer_ptr = new SingleSphere{this};

	sphere.set_center(0.0);
	sphere.set_radius(85.0);
}
