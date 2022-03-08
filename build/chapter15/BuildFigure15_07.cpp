// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 15.7
// Instances are discussed in Section 21.4
// Beveled cylinders are discussed in Section 21.5

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "GeometricObjects/BeveledCylinder.h"
#include "GeometricObjects/Instance.h"
#include "Materials/Phong.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(650);	  		
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 0, 100});
	pinhole_ptr->set_lookat({0, 0, 0});
	pinhole_ptr->set_view_distance(6000); 
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction({20, 0, 20});
	light_ptr2->scale_radiance(3.0);
	add_light(light_ptr2);
		
	
	// beveled cylinder
	
	float bottom 		= -2.0;
	float top 			= 2.0;
	float radius 		= 1.0;
	float bevel_radius 	= 0.2;
	
	auto cylinder_ptr1 = make_shared<BeveledCylinder>(bottom, top, radius, bevel_radius);
	
	for (int j = 0; j < 4; j++) {
		float exp;
	
		if (j == 0) exp = 5;
		if (j == 1) exp = 20;
		if (j == 2) exp = 100;
		if (j == 3) exp = 1000;
	
		auto phong_ptr = make_shared<Phong>();
		phong_ptr->set_ka(0.25); 					
		phong_ptr->set_kd(0.6);
		phong_ptr->set_cd(0.5);
		phong_ptr->set_ks(0.2);
		phong_ptr->set_exp(exp);
	
		Instance* cylinder_ptr2 = new Instance(cylinder_ptr1);
		cylinder_ptr2->translate({-3.75 + 2.5 * j, 0, 0});
		cylinder_ptr2->set_material(phong_ptr);
		add_object(cylinder_ptr2);
	}
}
