// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.21

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;

	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_pixel_size(0.5);
	vp.set_samples(num_samples); 
	
	tracer_ptr = new RayCast(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
	set_ambient_light(ambient_ptr);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(-5, 0, 0); 
//	pinhole_ptr->set_vpd(850.0);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(100, 50, 150);
	light_ptr2->scale_radiance(3.0); 
	add_light(light_ptr2);

	Sphere*	sphere_ptr1 = new Sphere(Point3D(10, -5, 0), 27); 
	sphere_ptr1->set_material(make_shared<Matte>(.25, .65, RGBColor{1,1,0}));
	add_object(sphere_ptr1);
	
	Sphere*	sphere_ptr2 = new Sphere(Point3D(-25, 10, -35), 27); 			
	sphere_ptr2->set_material(make_shared<Matte>(.15, .85, RGBColor{.71, .40, .16}));
	add_object(sphere_ptr2);
	
	Plane* plane_ptr = new Plane(Point3D(0, 0, -50), Normal(0, 0, 1)); 
	plane_ptr->set_material(make_shared<Matte>(.15, .5, RGBColor{0, .4, .2}));
	add_object(plane_ptr);
}
