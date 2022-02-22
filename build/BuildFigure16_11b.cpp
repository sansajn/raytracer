// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 16.11(b)

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/SolidCylinder.h"
#include "Materials/Phong.h"
#include "Materials/Matte.h"

using std::make_unique, std::make_shared, std::move;

void World::build(){
	constexpr int num_samples = 16;

	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	auto camera_ptr = make_unique<Pinhole>();
	camera_ptr->set_eye({0, 7, 10});
	camera_ptr->set_lookat({0, -1.5, 0});
	camera_ptr->set_view_distance(1200);     
	camera_ptr->compute_uvw(); 
	set_camera(move(camera_ptr));
		
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(3, 10, 2); 
	light_ptr1->set_color(1, 0, 0);				// red
	light_ptr1->scale_radiance(12.0);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(-3, 10, 2); 
	light_ptr2->set_color(0, 1, 0);				// green
	light_ptr2->scale_radiance(12.0);
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	PointLight* light_ptr3 = new PointLight;
	light_ptr3->set_location(0, 10, -3); 
	light_ptr3->set_color(blue);
	light_ptr3->scale_radiance(12.0);
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	// sphere
	
	Sphere*	sphere_ptr1 = new Sphere;  
	sphere_ptr1->set_material(make_shared<Matte>(.6, .2, .5));
	add_object(sphere_ptr1);	
	
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->set_ka(0.0); 
	matte_ptr2->set_kd(0.35);
	matte_ptr2->set_cd(0.7); 	
	
	Plane* plane_ptr = new Plane(Point3D(0, -3, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(0, .35, .7));
	add_object(plane_ptr);
}

