// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figures 30.13(a) and 30.13(b).

// The build function is the same for both figures. 
// The difference is in the BeveledCylinder contructor, as discussed on page 685.

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Noise/CubicNoise.h"
#include "Utilities/Image.h"
#include "Textures/TInstance.h"
#include "Textures/Checker3D.h"
#include "Textures/RampFBmTexture.h"
#include "Materials/SV_Matte.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/BeveledCylinder.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);	
	
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({20, 10, 40});
	pinhole_ptr->set_lookat({0, 1, 0});
	pinhole_ptr->set_view_distance(9000.0); 
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(30, 40, 20);
	light_ptr1->scale_radiance(2.5);     
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);


	// marble ramp image

	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("assets/BlueMarbleRamp.ppm");
	
	// marble parameters
	
	int 	num_octaves = 6;
	float 	fbm_amount 	= 6.0;	
	RampFBmTexture* ramp_marble_ptr = new RampFBmTexture(image_ptr, num_octaves, fbm_amount);		
			
			
	// transformed marble texture
	
	// These intrinsic texture transformations are only to make the marble look "good"
	// on the cylinder.	
	// They are unrelated to the translation in the y direction that's applied to the 
	// marble on the top and bottom cylinder bevels in Figure 30.13(a).	

	TInstance* marble_ptr = new TInstance;
	marble_ptr->set_texture(ramp_marble_ptr);
	marble_ptr->scale(0.4);  
	marble_ptr->rotate_x(270);
	marble_ptr->rotate_y(30);
	marble_ptr->rotate_z(30);
	
		
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.35);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(marble_ptr);
	
	
	// cylinder parameters
	
	double bottom 		= 0.0;
	double top 			= 2.0;
	double radius 		= 1.0;
	double bevel_radius = 0.5;
	
	BeveledCylinder* cylinder_ptr = new BeveledCylinder(bottom, top, radius, bevel_radius);
	cylinder_ptr->set_material(sv_matte_ptr);
	add_object(cylinder_ptr);	
	
	
			
	// ground plane
	
	auto matte_ptr1 = make_shared<Matte>();
	matte_ptr1->set_ka(0.3);
	matte_ptr1->set_kd(0.85);
	matte_ptr1->set_cd(RGBColor{.75});
	
	Plane* plane_ptr1 = new Plane(Point3D(0, 0.01, 1), Normal(0, 1, 0)); 
	plane_ptr1->set_material(matte_ptr1);
	add_object(plane_ptr1);	
		
	
	// plane perpendicular to x axis
	
	auto matte_ptr2 = make_shared<Matte>();
	matte_ptr2->set_ka(0.25);		
	matte_ptr2->set_kd(0.75);
	matte_ptr2->set_cd(RGBColor{.75});
	
	Plane* plane_ptr2 = new Plane(Point3D(-1.5, 0, 0), Normal(1, 0, 0)); 
	plane_ptr2->set_material(matte_ptr2);
	add_object(plane_ptr2);

	
	// plane perpendicular to z axis
	
	auto matte_ptr3 = make_shared<Matte>();
	matte_ptr3->set_ka(0.25);		
	matte_ptr3->set_kd(0.5);
	matte_ptr3->set_cd(RGBColor{.6});
	
	Plane* plane_ptr3 = new Plane(Point3D(0, 0, -1.5), Normal(0, 0, 1)); 
	plane_ptr3->set_material(matte_ptr3);
	add_object(plane_ptr3);
}
