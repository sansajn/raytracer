// OpenPartCylinder test scene

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/OpenCylinder.h"
#include "GeometricObjects/OpenPartCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);

	tracer_ptr = new RayCast(this);

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 3, 5});
	pinhole_ptr->set_lookat({0, 0, 0});
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));

	PointLight * light = new PointLight;
	light->set_location({0, 150, 200});
	light->scale_radiance(1.5);
	light->set_shadows(true);
	add_light(light);

	// cylinder
	float bottom	= 0;
	float top 		= 1;
	float radius 	= 1;
	float phi_min 	= 10;
	float phi_max 	= 270;

	OpenPartCylinder* cylinder = new OpenPartCylinder{bottom, top, radius, phi_min, phi_max};
	cylinder->set_material(make_unique<Matte>(.85, 0.6, RGBColor{1, .5, 0}));
	add_object(cylinder);
}
