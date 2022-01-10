// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 17.14

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Samplers/MultiJittered.h"
#include "Lights/AmbientOccluder.h"
#include "Cameras/Pinhole.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/OpenPartCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	int num_samples = 256;
	
	vp.set_hres(400);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);  
	
	tracer_ptr = new RayCast(this);
		
	AmbientOccluder * occluder_ptr = new AmbientOccluder;
	occluder_ptr->scale_radiance(1.0);
	occluder_ptr->set_min_amount(0.0);
	occluder_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	set_ambient_light(occluder_ptr);
			
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({-10, 2, 0});
	pinhole_ptr->set_lookat({0.35, 0.45, 0});
	pinhole_ptr->set_view_distance(1500);	
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	// cylinder
	
	float bottom	= 0;
	float top 		= 1;
	float radius 	= 1;
	float phi_min 	= 0;
	float phi_max 	= 180;
	
	OpenPartCylinder* cylinder_ptr = new OpenPartCylinder(	bottom, 
															top, 
															radius, 
															phi_min, 
															phi_max);
	cylinder_ptr->set_material(make_shared<Matte>(.85, .6, RGBColor{1, .5, 0}));
	add_object(cylinder_ptr);	
	
	
	// ground plane
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.5, .75, white));
	add_object(plane_ptr);	
}
