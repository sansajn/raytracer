// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.7
// Instances are covered in Chapter 21

#include "World/World.h"
#include "Samplers/MultiJittered.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Materials/Emissive.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Triangle.h"
#include "GeometricObjects/Instance.h"
#include "Lights/PointLight.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>(Point3D{25, 200, 100}, Point3D{-.5, 0, 0}, 8000.0f);
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(1, 5, 0);
	light_ptr1->scale_radiance(3.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	// yellow triangle
	Triangle* triangle_ptr1 = new Triangle(Point3D(2, 0.5, 5), Point3D(2, 1.5, -5), Point3D(-1, 0, -4)); 
	triangle_ptr1->set_material(make_shared<Matte>(.25, .75, RGBColor{1,1,0}));
	add_object(triangle_ptr1);
	
	// dark green triangle (transformed)
	Instance* triangle_ptr2 = new Instance(make_shared<Triangle>(Point3D(2, 1, 5), Point3D(2, 0.5, -5), Point3D(-1, -1, -4)));
	triangle_ptr2->rotate_y(120);
	triangle_ptr2->set_material(make_shared<Matte>(.25, .75, RGBColor{0, .5, .41}));
	add_object(triangle_ptr2);
	
	// brown triangle (transformed)
	Instance* triangle_ptr3 = new Instance(make_shared<Triangle>(Point3D(2, 0, 5), Point3D(2, 1, -5), Point3D(-1, 0, -4)));
	triangle_ptr3->rotate_y(240);
	triangle_ptr3->set_material(make_shared<Matte>(.25, .75, RGBColor{.71, .4, .16}));
	add_object(triangle_ptr3);
}	
