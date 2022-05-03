// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 11.13
// The light probe mapping is described in Chapter 29
// There are no light sources in this scene

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Spherical.h"
#include "Materials/SV_Matte.h"
#include "Textures/ImageTexture.h"
#include "Mappings/LightProbe.h"
#include "GeometricObjects/Instance.h"
#include "Utilities/Image.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(800);			
	vp.set_vres(400); 
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new RayCast(this);	
	
	auto spherical_ptr = make_unique<Spherical>();
	spherical_ptr->set_eye(Point3D{0});
	spherical_ptr->set_lookat({0, 0, -100});
	spherical_ptr->set_horizontal_fov(360);  
	spherical_ptr->set_vertical_fov(180);  
	spherical_ptr->compute_uvw(); 
	set_camera(move(spherical_ptr));
	
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("assets/uffizi_probe_large.ppm");

	LightProbe* light_probe_ptr = new LightProbe;     	
	light_probe_ptr->set_map_type(panoramic);
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	
	auto unit_sphere_ptr = make_shared<Sphere>();
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->scale(Vector3D{1000000});
	sphere_ptr->set_material(make_shared<SV_Matte>(1.0, 0.85, image_texture_ptr));
	add_object(sphere_ptr);
}
