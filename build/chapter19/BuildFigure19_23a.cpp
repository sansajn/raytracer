// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 19.23(a)

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
//	tracer_ptr = new FirstHit(this);
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>(Point3D{0,5,10}, Point3D{0}, 1200);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	// point light
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(10, 13, 20);
	light_ptr1->scale_radiance(3.0); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);	

	// solid cylinder
	// the following values for bottom, top, and radius can also be the default values
	// by setting them in the SolidCylinder default constructor
	
	float bottom = -1,
		top = 1,
		radius = 1;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(make_shared<Matte>(.3, .6, yellow));
	add_object(cylinder_ptr);
	
	// ground plane
	Plane* plane_ptr1 = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr1->set_material(make_shared<Matte>(.25, 1, white));
	add_object(plane_ptr1);
}


