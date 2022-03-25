// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.16

// As this build function does not use the "panoramic" option for the 
// LightProbe mapping, the resulting image is the mirror image of Figure 11.8(b).

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/FishEye.h"
#include "Utilities/Image.h"
#include "Mappings/LightProbe.h"
#include "Textures/ImageTexture.h"
#include "Textures/ConstantColor.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Instance.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(900);			
	vp.set_vres(900); 
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	
	tracer_ptr = new RayCast(this);	
	
	auto fisheye_ptr = make_unique<FishEye>();
	fisheye_ptr->set_eye(Point3D{0});
	fisheye_ptr->set_lookat({0, 0, -100});
	fisheye_ptr->set_fov(360);
	fisheye_ptr->compute_uvw(); 
	set_camera(move(fisheye_ptr));
	
	Image* image_ptr = new Image;
//	image_ptr->read_ppm_file("uffizi_probe_small.ppm");   // development
	image_ptr->read_ppm_file("assets/uffizi_probe_large.ppm");   // production

	LightProbe* light_probe_ptr = new LightProbe;     	
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->set_mapping(light_probe_ptr);
	
	auto unit_sphere_ptr = make_shared<Sphere>();
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->scale(Vector3D{1000000.0});
	sphere_ptr->set_material(make_shared<SV_Matte>(1, .85, image_texture_ptr));
	add_object(sphere_ptr);
}
