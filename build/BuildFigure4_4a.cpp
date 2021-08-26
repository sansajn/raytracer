#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Materials/Matte.h"
#include "Lights/PointLight.h"
#include "Samplers/Regular.h"
#include "Cameras/Orthographic.h"

void World::build() {
	constexpr int num_samples = 1;  // use 1 for 4.4(a) and 16 for 4.4(b)

	Regular * uniform_ptr = new Regular{num_samples};

	vp.set_hres(32);
	vp.set_vres(32);
	vp.set_pixel_size(1.0);
	vp.set_sampler(uniform_ptr);

	background_color = black;
	tracer_ptr = new RayCast{this};

	Orthographic * orthographic_ptr = new Orthographic;
	orthographic_ptr->set_eye(0, 0, 100);
	orthographic_ptr->set_lookat(0.0);
	set_camera(orthographic_ptr);

	ambient_ptr = new Ambient;

	PointLight * light_ptr = new PointLight;
	light_ptr->set_location(100, 100, 200);
	light_ptr->scale_radiance(2.0);
	add_light(light_ptr);

	Matte * matte_ptr = new Matte;
	matte_ptr->set_ka(0.2);
	matte_ptr->set_kd(0.8);
	matte_ptr->set_cd(1, 1, 0);				// yellow

	Sphere * sphere_ptr = new Sphere{Point3D{0}, 13.0};
	sphere_ptr->set_material(matte_ptr);
	add_object(sphere_ptr);
}
