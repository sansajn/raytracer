// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the Scene for Figure 24.10
// Texture mapping is discussed in Chapter 29

#include "World/World.h"
#include "Tracers/Whitted.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "Mappings/LightProbe.h"
#include "Materials/Reflective.h"
#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/Instance.h"
#include "Textures/ImageTexture.h"
#include "Utilities/Image.h"

using std::vector;
using std::make_unique, std::make_shared, std::move, std::shared_ptr;

void World::build() {
	constexpr int num_samples = 16;

	vp.set_hres(600);			
	vp.set_vres(600);  
	vp.set_samples(num_samples);
	vp.set_pixel_size(1.0);
	vp.set_max_depth(10);
	
	tracer_ptr = new Whitted(this);		
			
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({400, 125, 500});
	pinhole_ptr->set_lookat({0.0, -50, 0});
	pinhole_ptr->set_view_distance(550);
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
	
	
	auto spheres = make_shared<Compound>();
		
	float  kr = 0.9;
	double radius = 100.0;
	
	// reflective sphere centered at the origin

	auto reflective_ptrc = make_shared<Reflective>();
	reflective_ptrc->set_ka(0.0); 
	reflective_ptrc->set_kd(0.0);
	reflective_ptrc->set_ks(0.0);
	reflective_ptrc->set_cd(RGBColor{0.0});
	reflective_ptrc->set_kr(kr);
	reflective_ptrc->set_cr(0.65, 0.75, 1.0);   // pale blue
		
	Sphere* sphere_ptr = new Sphere(Point3D(0.0), radius);
	sphere_ptr->set_shadows(false);
	sphere_ptr->set_material(reflective_ptrc);
	spheres->add_object(sphere_ptr);
	
	// define materials for the surrounding spheres
	
	vector<shared_ptr<Reflective>> materials;
	
	auto reflective_ptr0 = make_shared<Reflective>();
	reflective_ptr0->set_ka(0.0); 
	reflective_ptr0->set_kd(0.0);
	reflective_ptr0->set_ks(0.0);
	reflective_ptr0->set_cd(RGBColor{0.0});
	reflective_ptr0->set_kr(kr);
	reflective_ptr0->set_cr(0.5, 1.0, 0.5);  // light green
	materials.push_back(reflective_ptr0);

	auto reflective_ptr1 = make_shared<Reflective>();
	reflective_ptr1->set_ka(0.0); 
	reflective_ptr1->set_kd(0.0);
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_cd(RGBColor{0.0});
	reflective_ptr1->set_kr(kr);
	reflective_ptr1->set_cr(0.4, 1.0, 1.0);  // cyan
	materials.push_back(reflective_ptr1);
	
	auto reflective_ptr2 = make_shared<Reflective>();
	reflective_ptr2->set_ka(0.0); 
	reflective_ptr2->set_kd(0.0);
	reflective_ptr2->set_ks(0.0);
	reflective_ptr2->set_cd(RGBColor{0.0});
	reflective_ptr2->set_kr(kr);
	reflective_ptr2->set_cr(1.0, 1.0, 0.4);  // lemon
	materials.push_back(reflective_ptr2);
	
	auto reflective_ptr3 = make_shared<Reflective>();
	reflective_ptr3->set_ka(0.0); 
	reflective_ptr3->set_kd(0.0);
	reflective_ptr3->set_ks(0.0);
	reflective_ptr3->set_cd(RGBColor{0.0});
	reflective_ptr3->set_kr(kr);
	reflective_ptr3->set_cr(1.0, 0.5, 1.0);  // mauve
	materials.push_back(reflective_ptr3);
	
	auto reflective_ptr4 = make_shared<Reflective>();
	reflective_ptr4->set_ka(0.0); 
	reflective_ptr4->set_kd(0.0);
	reflective_ptr4->set_ks(0.0);
	reflective_ptr4->set_cd(RGBColor{0.0});
	reflective_ptr4->set_kr(kr);
	reflective_ptr4->set_cr(1.0, 0.75, 0.25);  // orange
	materials.push_back(reflective_ptr4);
	
	auto reflective_ptr5 = make_shared<Reflective>();
	reflective_ptr5->set_ka(0.0); 
	reflective_ptr5->set_kd(0.0);
	reflective_ptr5->set_ks(0.0);
	reflective_ptr5->set_cd(RGBColor{0.0});
	reflective_ptr5->set_kr(kr);
	reflective_ptr5->set_cr(0.5, 0.5, 1.0);  // blue
	materials.push_back(reflective_ptr5);
	

	// define ring of reflective spheres that just touch the center sphere
	// these are initially in the (x, z) plane
	
	float  num_spheres = 6;
	double theta = 0.0;
	double delta_theta = 2.0 * PI<double> / num_spheres;
	
	for (int j = 0; j < num_spheres; j++) {
		Point3D center((2.0 * radius) * sin(theta), 0.0, (2.0 * radius) * cos(theta));
		Sphere* sphere_ptr = new Sphere(center, radius);
		sphere_ptr->set_material(materials[j]);
		spheres->add_object(sphere_ptr);
		theta += delta_theta;
	}
		
	// now rotate the spheres

	Instance* rotated_spheres_ptr = new Instance(spheres);
	rotated_spheres_ptr->rotate_x(40.0);
	rotated_spheres_ptr->rotate_z(-40.0);
	add_object(rotated_spheres_ptr);

	
	// large sphere with Uffizi image
	
	Image* image_ptr = new Image;
	image_ptr->read_ppm_file("assets/uffizi_probe_large.ppm");   // for production
	
	LightProbe* light_probe_ptr = new LightProbe;     		
	
	ImageTexture* texture_ptr = new ImageTexture(image_ptr); 
	texture_ptr->set_mapping(light_probe_ptr);
	
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(1.0);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	auto unit_sphere_ptr = make_shared<Sphere>();
	unit_sphere_ptr->set_shadows(false);	
	
	Instance* sphere_ptr1 = new Instance(unit_sphere_ptr); 
	sphere_ptr1->set_material(sv_matte_ptr);
	sphere_ptr1->scale(Vector3D{1000000.0});
	add_object(sphere_ptr1);
}
