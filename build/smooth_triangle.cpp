// SmoothTriangle test scene
#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Materials/Phong.h"
#include "Materials/Matte.h"
#include "GeometricObjects/SmoothTriangle.h"

#include "Utilities/math_disp.hpp"
#include <iostream>
using std::cout;

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = /*16*/1;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);

	background_color = RGBColor{.9};

	tracer_ptr = new RayCast(this);

	auto pinhole = make_unique<Pinhole>();
	pinhole->set_eye({10, 12, 18});
	pinhole->set_lookat({0, 0, 0});
	pinhole->set_view_distance(4000);
	pinhole->compute_uvw();
	set_camera(move(pinhole));

	Directional * light = new Directional;
	light->set_direction(20, 25, 5);
	light->scale_radiance(3.0);
	light->set_shadows(false);
	add_light(light);

	auto phong = make_shared<Phong>();
	phong->set_ka(0.25);
	phong->set_kd(0.75);
	phong->set_cd(RGBColor{0.2, 0.5, 0.4});
	phong->set_ks(0.2);
	phong->set_exp(20.0);

	auto matte = make_shared<Matte>();
	matte->set_ka(0.25);
	matte->set_kd(0.75);
	matte->set_cd(RGBColor{0.2, 0.5, 0.4});

	// s algoritmu pre teselaciu gule
	Point3D const v0 = {0,1,0},
		v1 = {0,0,1},
		v2 = {0.8660254037844387, 0, -0.4999999999999998};

	SmoothTriangle * triangle = new SmoothTriangle{v0, v1, v2};
	triangle->n0 = v0;
	triangle->n1 = v1;
	triangle->n2 = v2;

	triangle->set_material(/*phong*/matte);
	add_object(triangle);


	// shoot ray
	Ray r{{10, 12, 18}, {-0.382747, -0.502746, -0.775081}};
	double tmin = 0;
	ShadeRec sr{*this};
	bool hit = triangle->hit(r, tmin, sr);
	if (hit) {
		// shade hit point
		sr.hit_an_object = true;
		sr.material_ptr = matte.get(); //phong.get();
		sr.hit_point = r.o + tmin*r.d;

		cout << "ray hit detected\n"
			<< "  local-point: " << sr.local_hit_point << "\n"
			<< "  normal: " << sr.normal << "\n"
			<< "  hit-point: " << sr.hit_point << "\n";

		RGBColor c = phong->shade(sr);
		cout << "  color: " << c << "\n";

		cout << "light direction: " << light->get_direction(sr) << "\n";
	}
	else
		cout << "ray not hit\n";
}
