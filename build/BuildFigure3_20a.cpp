// scene with two spheres and plane
#include "World/World.h"
#include "Tracers/MultipleObjects.h"
#include "GeometricObjects/Plane.h"

void World::build() {
	vp.set_hres(200);
	vp.set_vres(200);

	background_color = black;
	tracer_ptr = new MultipleObjects{this};

	// sphere1
	Sphere * s1 = new Sphere;
	s1->set_center(0, -25, 0);
	s1->set_radius(80);
	s1->set_color(1, 0, 0);  // red
	add_object(s1);

	// sphere2
	Sphere * s2 = new Sphere{Point3D{0, 30, 0}, 60};
	s2->set_color(1, 1, 0);  // yellow
	add_object(s2);

	// plane
	Plane * p = new Plane{Point3D{0, 0, 0}, Normal{0, 1, 1}};
	p->set_color(.0, .3, .0);
	add_object(p);
}
