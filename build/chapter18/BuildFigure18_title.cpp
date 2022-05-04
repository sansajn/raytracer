// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
// This builds the scene for the Chapter 18 page 1 image

// The illumination is from a lemon environment light as discussed in Section 18.10
// and a jittered directional light from Exercise 18.3. The code for the function
// JitteredDirectional::get_direction is analogous to the code in LIsting 18.18. 
// The un-jittered direction should be normalized in the set_direction function, and the 
// jittered direction should be normalized in the get_direction function. The set_jittered_amount 
// function sets "r". The simplest way to implement the JitteredDirectional class is to let it inherit 
// from Directional.

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
#include "GeometricObjects/ConcaveHemisphere.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/EnvironmentLight.h"
#include "Lights/Directional.h"
#include "Lights/JitteredDirectional.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 256;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	vp.set_max_depth(0);
		
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
		
	JitteredDirectional* light_ptr = new JitteredDirectional;
	light_ptr->set_direction(150, 50, -50);   
	light_ptr->set_color(1.0, 0.25, 0.0);  // orange
	light_ptr->set_jitter_amount(0.2);
	light_ptr->scale_radiance(4.0);       
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->set_ce({1.0, 1.0, 0.5}); 	// lemon
	emissive_ptr->scale_radiance(0.9);
	
	ConcaveHemisphere* hemisphere_ptr = new ConcaveHemisphere;
	hemisphere_ptr->set_radius(1000000.0);
	hemisphere_ptr->set_material(emissive_ptr);
	hemisphere_ptr->set_shadows(false);
	add_object(hemisphere_ptr);
	
	EnvironmentLight* environmentLight_ptr = new EnvironmentLight;
	environmentLight_ptr->set_material(emissive_ptr);
	environmentLight_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	environmentLight_ptr->set_shadows(true);
	add_light(environmentLight_ptr);
	
	
	constexpr float ka = 0.2;  // commom ambient reflection coefficient
	
	// large sphere
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(make_shared<Matte>(ka, .6, RGBColor{.75}));
	add_object(sphere_ptr1);
	
	// small sphere
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(make_shared<Matte>(ka, .4, RGBColor{.25, 1, .35}));
	add_object(sphere_ptr2);
	
	// medium sphere
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(make_shared<Matte>(ka, .5, RGBColor{.75}));
	add_object(sphere_ptr3);

	
	// cylinder
	auto phong_ptr = make_shared<Phong>();
	phong_ptr->set_ka(ka); 
	phong_ptr->set_kd(0.25);
	phong_ptr->set_cd(RGBColor{.60});
	phong_ptr->set_ks(0.5);
	phong_ptr->set_exp(100);
	
	constexpr float bottom = 0.0,
		top = 85,
		radius = 22;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(phong_ptr);
	add_object(cylinder_ptr);

	// box
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->set_material(make_shared<Matte>(ka, .5, RGBColor{.95}));
	add_object(box_ptr);
	
	// ground plane 
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.15, .5, RGBColor{.7}));
	add_object(plane_ptr);
}
