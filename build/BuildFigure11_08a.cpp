// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 11.8
// The light probe mapping is described in Chapter 29
// There are no light sources in this scene

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/FishEye.h"
#include "Utilities/Image.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Instance.h"
#include "Textures/ImageTexture.h"
#include "Textures/LightProbe.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);			
	vp.set_vres(600); 
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new RayCast(this);	
		
	auto fisheye_ptr = make_unique<FishEye>();
	
	fisheye_ptr->set_eye(0); 
	fisheye_ptr->set_lookat(0, 0, -100);
	
	fisheye_ptr->set_fov(180);			// For Figure 11.8(a)
//	fisheye_ptr->set_fov(360);	 		// For Figure 11.8(b)
	
//	fisheye_ptr->set_lookat(0, 100, 0);	// For Figure 11.8(c) - camera looks vertically up
//	fisheye_ptr->set_fov(200);		
	
	fisheye_ptr->compute_uvw(); 
	set_camera(move(fisheye_ptr));

	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("assets/uffizi_probe.ppm");   // for development
//	image_ptr->read_ppm_file("uffizi_probe_large.ppm");   // for production

	LightProbe* light_probe_ptr = new LightProbe;     	
	light_probe_ptr->set_map_type(panoramic);
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
//	unit_sphere_ptr->set_shadows(false);
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->scale(1000000);
	sphere_ptr->set_material(make_shared<SV_Matte>(1.0, 0.85, image_texture_ptr));
	add_object(sphere_ptr);
}
