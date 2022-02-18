// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This tests the solid cylinder built as a compound object

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>(Point3D{0,5,10}, Point3D{0}, 1200);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
		
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(10, 13, 20);
	light_ptr->scale_radiance(3.0); 
	light_ptr->set_shadows(true);
	add_light(light_ptr);	

	auto matte_ptr1 = make_shared<Matte>();
	matte_ptr1->set_ka(0.3);    
	matte_ptr1->set_kd(0.6);
	matte_ptr1->set_cd(cyan);
	
	auto matte_ptr2 = make_shared<Matte>();
	matte_ptr2->set_ka(0.3);    
	matte_ptr2->set_kd(0.6);
	matte_ptr2->set_cd(yellow);
	
	constexpr float bottom = -1.0,
		top = 1.0,
		radius = 1.0;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_bottom_material(matte_ptr1); 	// cyan
	cylinder_ptr->set_top_material(matte_ptr1); 	// cyan
	cylinder_ptr->set_wall_material(matte_ptr2); 	// yellow
	add_object(cylinder_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.25, 1, white));
	add_object(plane_ptr);
}
