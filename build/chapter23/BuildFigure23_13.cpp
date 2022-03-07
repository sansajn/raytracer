// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.13
// The scene is the goldfish model by James McNee
// The fish faces along the +ve z axis
// The low resolution model has 1.4K triangles
// The high resolution model has 22K triangles

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Materials/Phong.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Instance.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	background_color = black;

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({75, 20, 80});
	pinhole_ptr->set_lookat({-0.05, -0.5, 0});
	pinhole_ptr->set_view_distance(1600);  	
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
		
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(0.75, 0.5, -0.15);     
	directional_ptr->scale_radiance(2.0); 
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);
	
	auto phong_ptr1 = make_shared<Phong>();
	phong_ptr1->set_ka(0.4); 
	phong_ptr1->set_kd(0.8);
	phong_ptr1->set_cd(RGBColor{1.0, 0.2, 0.0});
	phong_ptr1->set_ks(0.5); 
	phong_ptr1->set_cs(RGBColor{1.0, 1.0, 0.0});
	phong_ptr1->set_exp(50.0);
	
	const char* file_name = "goldfish_low_res.ply";
//	const char* file_name = "goldfish_high_res.ply";
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_flat_triangles(file_name);		
//	grid_ptr->read_smooth_triangles(file_name);		
	grid_ptr->set_material(phong_ptr1);    
	grid_ptr->setup_cells();
	add_object(grid_ptr);
}
