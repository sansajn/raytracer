// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.9(b).

// Ambient occlusion is used to bring out detail in the shadows. For example,
// it makes the dragon's upper teeth visible, but requires at least 100 samples
// per pixel to reduce the noise to an acceptable level.
// Alternatively, you can use constant ambient illumination.
// The image was rendered with smooth shading, but flat shading builds quicker.

// The Whitted tracer and Reflective material are discussed in Chapter 24.

#include "World/World.h"
#include "Tracers/Whitted.h"
#include "Samplers/MultiJittered.h"
#include "Cameras/Pinhole.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/Directional.h"
#include "Materials/Phong.h"
#include "Materials/Reflective.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 24;
	
	vp.set_hres(600);      
	vp.set_vres(600);    
	vp.set_samples(num_samples);
	vp.set_max_depth(1);
	
	tracer_ptr = new Whitted(this);
	background_color = black;
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(1.0);
//	set_ambient_light(ambient_ptr);
		
	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->set_min_amount(0.25);		
	occluder_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	set_ambient_light(occluder_ptr);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({-6, 5, 11});
	pinhole_ptr->set_lookat({-0.009 , 0.11, 0});
	pinhole_ptr->set_view_distance(37500);  
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0.5, 1, 0.75);
	light_ptr->scale_radiance(1.0);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	auto phong_ptr = make_shared<Phong>();
	phong_ptr->set_ka(0.2); 
	phong_ptr->set_kd(0.95); 
	phong_ptr->set_cd(RGBColor{1, 0.6, 0});   // orange
	phong_ptr->set_ks(0.5);  
	phong_ptr->set_exp(20); 
	phong_ptr->set_cs(RGBColor{1, 0.6, 0});   // orange
		
	const char* file_name = "assets/dragon_vrip.ply";
	Grid* dragon_ptr = new Grid(new Mesh);
//	dragon_ptr->read_flat_triangles(file_name);
	dragon_ptr->read_smooth_triangles(file_name);
	dragon_ptr->set_material(phong_ptr); 
	dragon_ptr->setup_cells();
	add_object(dragon_ptr);

	
	auto reflective_ptr = make_shared<Reflective>();
	reflective_ptr->set_ka(0.2); 
	reflective_ptr->set_kd(0.75);
	reflective_ptr->set_cd(RGBColor{.5});
	reflective_ptr->set_ks(0.0);
	reflective_ptr->set_exp(20);
	reflective_ptr->set_kr(0.5);  
	reflective_ptr->set_cr(0.8, 1.0, 0.8);    
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.055, 0), Normal(0, 1, 0)); 	
	plane_ptr->set_material(reflective_ptr);
	add_object(plane_ptr);	
}
