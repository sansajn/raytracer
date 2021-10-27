#include "World.h"
#include "Orthographic.h"

Camera * Orthographic::clone() const {
	return new Orthographic{*this};
}

void Orthographic::render_scene(World const & w, float x, int offset) {
	compute_uvw();
	ViewPlane const & vp = w.vp;
	int hres = vp.hres;
	int vres = vp.vres;
	float s = vp.s;

	Ray ray;
	ray.d = Vector3D{0, 0, -1};

	for (int r = 0; r < vres; ++r)  // up
		for (int c = 0; c < hres; ++c) {  // across
			RGBColor pixel_color = black;

			for (int j = 0; j < vp.num_samples; ++j) {
				Point2D sp = vp.sampler_ptr->sample_unit_square();  // sample point in [0,1]x[0,1]
				Point2D pp{s * (c - 0.5f*hres + sp.x) + x, s * (r - 0.5f*vres + sp.y)};  // sample point on a pixel
				ray.o = Point3D{0, 0, eye.z} + u*pp.x + v*pp.y;
				pixel_color += w.tracer_ptr->trace_ray(ray);
			}

			pixel_color /= vp.num_samples;  // average the colors
			w.display_pixel(r, c + offset, pixel_color);
		}
}
