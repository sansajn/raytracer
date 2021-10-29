// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.15
// Instances are discussed in Section 21.4
// Beveled cylinders are discussed in Section 21.5

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Lights/Directional.h"
#include "Cameras/Pinhole.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/BeveledCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(650);	  		
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye(0, 0, 100);
	pinhole_ptr->set_lookat(0, 0, 0);
	pinhole_ptr->set_view_distance(6000);
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(20, 0, 20);
	light_ptr2->scale_radiance(3.0);
	add_light(light_ptr2);
	
	// beveled cylinder
	
	float bottom 		= -2.0;
	float top 			= 2.0;
	float radius 		= 1.0;
	float bevel_radius 	= 0.2;
	
	auto cylinder_ptr1 = make_shared<BeveledCylinder>(bottom, top, radius, bevel_radius);
	
	for (int j = 0; j < 4; j++) {
		Instance* cylinder_ptr2 = new Instance(cylinder_ptr1);
		cylinder_ptr2->translate(-3.75 + 2.5 * j, 0, 0);
		cylinder_ptr2->set_material(make_shared<Matte>(0.25, 0.1 + 0.3*j, RGBColor{0.5, 0.5, 0.5}));
		add_object(cylinder_ptr2);
	}
}
