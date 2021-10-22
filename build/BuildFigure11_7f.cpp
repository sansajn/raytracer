// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 11.7
// It uses a grid acceleration scheme (Chapter 22), a spherical texture mapping (Chapter 29),
// and a 3D checker (Chapter 30).
// You can test the fisheye camera without these features by doing the following:
// remove the grid code
// add the boxes directly to the world (I've left commented out code for doing this)
// don't use the skydome. This will give you a black background like the boxes image in 
// Chapter 9
// use a Matte material on the plane

// The code for the image class is in the Chapter 29 directory

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Cameras/FishEye.h"
#include "Lights/PointLight.h"
#include "Textures/Checker3D.h"
#include "Textures/SphericalMap.h"
#include "Textures/ImageTexture.h"
#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Instance.h"
#include "Utilities/Image.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
		
	// fisheye camera for the other parts
	
	auto fisheye_ptr = make_unique<FishEye>();

	// for part (f)
	// for this image the skydome is the only object in the scene
	// you need to comment out the two statements:
	// add_object(grid_ptr);
	// add_object(plane_ptr);
	
	fisheye_ptr->set_eye(0, 0, 0);     
	fisheye_ptr->set_lookat(0, 1, 0);
	fisheye_ptr->set_fov(180);


	// for part b, ..., f

	fisheye_ptr->compute_uvw();
	set_camera(move(fisheye_ptr));


	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(150, 200, 65);  
	light_ptr1->scale_radiance(5.25);
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	

	// skydome with clouds
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("assets/CloudsSmall.ppm");
	
	SphericalMap* spherical_map_ptr = new SphericalMap; 
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(spherical_map_ptr);
	
	Instance* sphere_ptr1 = new Instance(new Sphere); 
	sphere_ptr1->scale(1000000);
	sphere_ptr1->set_material(make_shared<SV_Matte>(1, 0.85, image_texture_ptr));
	add_object(sphere_ptr1);
}
