// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.11(b)

// Inspite of my best efforts, my ray tracer now renders the BilliardBall.ppm file shown 
// in Figure 29.11(a) in cyan instead of majenta. The color is majenta when the file is
// opened in GraphicConverter, and the thumbnail is also majenta. 
// Cyan is the wrong color for the number 9 ball.


#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Utilities/Image.h"
#include "Mappings/SphericalMap.h"
#include "Textures/ImageTexture.h"
#include "Textures/ConstantColor.h"
#include "Materials/Matte.h"
#include "Materials/SV_Phong.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);
		
	background_color = black;
	
	tracer_ptr = new RayCast(this);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	auto camera_ptr = make_unique<Pinhole>();
	camera_ptr->set_eye({50, 10, 50});
	camera_ptr->set_lookat(Point3D{0});
	camera_ptr->set_view_distance(11000.0); 
	camera_ptr->compute_uvw();     
	set_camera(move(camera_ptr));
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location({100, 50, 50});
	light_ptr1->scale_radiance(1.5); 
	light_ptr1->set_shadows(true); 
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location({100, 200, -100});
	light_ptr2->scale_radiance(1.5);
	light_ptr2->set_shadows(true);   
	add_light(light_ptr2);
	
	
	// image:					

	Image* image_ptr = new Image;				
	image_ptr->read_ppm_file("assets/BilliardBall.ppm");
	
	
	// mapping:
	
	SphericalMap* map_ptr = new SphericalMap; 
	
	
	// image based texture:  
	
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr); 
	texture_ptr->set_mapping(map_ptr);
	
	
	// textured material:

	auto sv_phong_ptr = make_shared<SV_Phong>();
	sv_phong_ptr->set_ka(0.5);
	sv_phong_ptr->set_kd(0.8);
	sv_phong_ptr->set_cd(texture_ptr);
	sv_phong_ptr->set_ks(0.25);
	sv_phong_ptr->set_exp(500.0);
	sv_phong_ptr->set_cs(new ConstantColor());
	
	
	// generic sphere:
	
	auto sphere_ptr = make_shared<Sphere>();
	sphere_ptr->set_material(sv_phong_ptr);
	
	
	// rotated sphere
	
	Instance* billard_ball_ptr = new Instance(sphere_ptr);
	billard_ball_ptr->rotate_y(-30);
	add_object(billard_ball_ptr);
	
	
	// plane
	Plane* plane_ptr = new Plane(Point3D(0, -1, 0), Vector3D(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.5, .5, RGBColor{.2, .75, .2}));
	add_object(plane_ptr);
}
