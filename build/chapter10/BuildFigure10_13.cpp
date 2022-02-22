// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 10.13

#include "World/World.h"
#include "Samplers/Regular.h"
#include "Tracers/RayCast.h"
#include "Lights/Ambient.h"
#include "Lights/Directional.h"
#include "Cameras/ThinLens.h"
#include "Textures/Checker3D.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(400);                                                               	  		
	vp.set_vres(300);
	vp.set_pixel_size(0.05);
	vp.set_sampler(make_unique<Regular>(num_samples));
	
	tracer_ptr = new RayCast(this);
	background_color = white;
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	auto thin_lens_ptr = make_unique<ThinLens>();
	thin_lens_ptr->set_sampler(new Regular(num_samples));
	thin_lens_ptr->set_eye(0, 6, 50);  
	thin_lens_ptr->set_lookat(0, 6, 0);
	thin_lens_ptr->set_view_distance(40.0);
	thin_lens_ptr->set_focal_distance(74.0); 
	thin_lens_ptr->set_lens_radius(1.0);	 
	thin_lens_ptr->compute_uvw();     
	set_camera(move(thin_lens_ptr));
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(1, 1, 1);     
	light_ptr->scale_radiance(7.5); 
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// box 1

	Checker3D* checker_ptr1 = new Checker3D;
	checker_ptr1->set_size(2.0);
	checker_ptr1->set_color1(1, 1, 0.33);  		// lemon
	checker_ptr1->set_color2(black);	 
	
	Box* box_ptr1 = new Box(Point3D(-9, 0, -1), Point3D(-3, 12, 0));
	box_ptr1->set_material(make_shared<SV_Matte>(0.5, 0.35, checker_ptr1));
	add_object(box_ptr1);
		
	
	// box 2
	
	Checker3D* checker_ptr2 = new Checker3D;
	checker_ptr2->set_size(2.0);
	checker_ptr2->set_color1(black);  	
	checker_ptr2->set_color2(0.1, 1, 0.5);	  	// green
	
	Box* box_ptr2 = new Box(Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24));
	box_ptr2->set_material(make_shared<SV_Matte>(0.5, 0.35, checker_ptr2));
	add_object(box_ptr2);
	
	
	// box 3
	
	Checker3D* checker_ptr3 = new Checker3D;
	checker_ptr3->set_size(2.0);
	checker_ptr3->set_color1(black);  	
	checker_ptr3->set_color2(1, 0.6, 0.15);	  	// orange
	
	Box* box_ptr3 = new Box(Point3D(8, 0, -49), Point3D(18, 15, -48));
	box_ptr3->set_material(make_shared<SV_Matte>(0.5, 0.35, checker_ptr3));
	add_object(box_ptr3);
	

	// ground plane
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(8.0);
	checker_ptr->set_color1(0.25);  			// gray
	checker_ptr->set_color2(white);	 
	
	Plane* plane_ptr1 = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr1->set_material(make_shared<SV_Matte>(0.5, 0.35, checker_ptr));
	add_object(plane_ptr1);
}
