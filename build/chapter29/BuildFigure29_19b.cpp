// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.19

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Utilities/Image.h"
#include "Textures/ImageTexture.h"
#include "Mappings/SphericalMap.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Instance.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 1;      	// for Figures 29.19(a) & (b)
//	constexpr int num_samples = 25;      	// for Figure 29.19(c)
	
	vp.set_hres(300);      
	vp.set_vres(300);    
	vp.set_samples(num_samples);
		
	background_color = black;
	
	tracer_ptr = new RayCast(this);
	
	auto camera_ptr = make_unique<Pinhole>();
	camera_ptr->set_eye({0, 0, 65});
	camera_ptr->set_lookat(Point3D{0});
//	camera_ptr->set_view_distance(9000.0);			// for Figure 29.19(a)
	camera_ptr->set_view_distance(9000.0 * 8.0);	// for Figure 29.19(b)
//	camera_ptr->set_view_distance(9000.0 * 20.0);	// for Figure 29.19(c)
	camera_ptr->compute_uvw();     
	set_camera(move(camera_ptr));
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(-0.25, 0.4, 1);		
	light_ptr->scale_radiance(2.5);  
	add_light(light_ptr);
	
	
	// image:					

	Image* image_ptr = new Image;				
	image_ptr->read_ppm_file("assets/EarthLowRes.ppm");
	
	
	// mapping:
	SphericalMap* map_ptr = new SphericalMap; 
	
	
	// image based texture:  
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	// generic sphere:
	auto sphere_ptr = make_shared<Sphere>();
	sphere_ptr->set_material(make_shared<SV_Matte>(.2, .8, texture_ptr));
	
	// rotated sphere
	Instance* earth_ptr = new Instance(sphere_ptr);
	earth_ptr->rotate_y(-72);
	earth_ptr->rotate_x(40);
	earth_ptr->rotate_z(20);
	add_object(earth_ptr);
}
