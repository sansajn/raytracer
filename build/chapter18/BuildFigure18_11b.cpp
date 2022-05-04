// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 18.11

#include "World/World.h"
#include "Samplers/MultiJittered.h"
#include "Samplers/Hammersley.h"
#include "Tracers/AreaLighting.h"
#include "Cameras/Pinhole.h"
#include "Materials/Emissive.h"
#include "Materials/Matte.h"
#include "Materials/Phong.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/ConcaveSphere.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/EnvironmentLight.h"

using std::make_unique, std::make_shared, std::move;

void World::build(void) {
	constexpr int num_samples = 100;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
		
	tracer_ptr = new AreaLighting(this);	
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);
			
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({100, 45, 100});
	pinhole_ptr->set_lookat({-10, 40, 0});
	pinhole_ptr->set_view_distance(400);  
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
	
	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->scale_radiance(0.90);
	emissive_ptr->set_ce(white);   	
		
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_shadows(false);
	add_object(sphere_ptr);
	
	EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	environment_light_ptr->set_material(emissive_ptr);
	environment_light_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	environment_light_ptr->set_shadows(true);
	add_light(environment_light_ptr);
	
	
	constexpr float ka = 0.2,  // commom ambient reflection coefficient
		ks = 1.0,  // commom specular reflection coefficient
//		exp = 10.0;  // for Figure 18.11(a)
		exp = 50.0;   	// for Figure 18.11(b)
//	float exp = 200.0;   	// for Figure 18.11(c)
	RGBColor cs(1, 0, 0); 	// common specular color
	
	// large sphere
	auto phong_ptr1 = make_shared<Phong>();
	phong_ptr1->set_ka(ka); 
	phong_ptr1->set_kd(0.6);
	phong_ptr1->set_cd(RGBColor{.75});
	phong_ptr1->set_ks(ks);
	phong_ptr1->set_exp(exp);
	phong_ptr1->set_cs(cs);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(phong_ptr1);
	add_object(sphere_ptr1);
	
	// small sphere
	auto phong_ptr2 = make_shared<Phong>();
	phong_ptr2->set_ka(ka); 
	phong_ptr2->set_kd(0.5);
	phong_ptr2->set_cd(RGBColor{.95});
	phong_ptr2->set_ks(ks);
	phong_ptr2->set_exp(exp);
	phong_ptr2->set_cs(cs);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(phong_ptr2);
	add_object(sphere_ptr2);
	
	
	// medium sphere
	auto phong_ptr3 = make_shared<Phong>();
	phong_ptr3->set_ka(ka); 
	phong_ptr3->set_kd(0.5);
	phong_ptr3->set_cd(RGBColor{.75});
	phong_ptr3->set_ks(ks);
	phong_ptr3->set_exp(exp);
	phong_ptr3->set_cs(cs);
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(phong_ptr3);
	add_object(sphere_ptr3);
	
	// cylinder
	auto phong_ptr4 = make_shared<Phong>();
	phong_ptr4->set_ka(ka); 
	phong_ptr4->set_kd(0.5);
	phong_ptr4->set_cd(RGBColor{.60});
	phong_ptr4->set_ks(ks);
	phong_ptr4->set_exp(exp);
	phong_ptr4->set_cs(cs);
	
	constexpr float bottom = 0.0,
		top = 85,
		radius = 22;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(phong_ptr4);
	add_object(cylinder_ptr);

	// box
	auto phong_ptr5 = make_shared<Phong>();
	phong_ptr5->set_ka(ka); 
	phong_ptr5->set_kd(0.5);
	phong_ptr5->set_cd(RGBColor{0.95});
	phong_ptr5->set_ks(ks);
	phong_ptr5->set_exp(exp);
	phong_ptr5->set_cs(cs);
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(phong_ptr5);
	add_object(box_ptr);
	
	// ground plane
	auto matte_ptr6 = make_shared<Matte>();
	matte_ptr6->set_ka(0.15); 
	matte_ptr6->set_kd(0.5);	
	matte_ptr6->set_cd(RGBColor{.7});
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(matte_ptr6);
	add_object(plane_ptr);
}
