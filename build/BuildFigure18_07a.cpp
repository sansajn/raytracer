// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 18.7

// For Figure 18.7(a):
// comment out 	set_ambient_light(ambient_ptr);
//				add_light(environmentLight_ptr);
// run with the ambient occluder light only

// For Figure 18.7(b):
// comment out 	set_ambient_light(ambient_occluder_ptr);
// run with the constant ambient light and the environment light
// it's necessary to run with a constant ambient light that has 
// zero radiance because the World's default ambient light has ls = 1.0

// For Figure 18.7(c):
// comment out 	set_ambient_light(ambient_ptr);
// run with the ambient occluder light and the environment light

#include "World/World.h"
#include "Samplers/MultiJittered.h"
#include "Tracers/AreaLighting.h"
#include "Cameras/Pinhole.h"
#include "Materials/Emissive.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/ConcaveSphere.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/EnvironmentLight.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	int num_samples = 100;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
		
	tracer_ptr = new AreaLighting(this);	
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.0);
//	set_ambient_light(ambient_ptr);				// for Figure 18.7(b)
		
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	ambient_occluder_ptr->set_min_amount(0.5);
	set_ambient_light(ambient_occluder_ptr);	// for Figure 18.7 (a) & (c)

			
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({100, 45, 100});
	pinhole_ptr->set_lookat({-10, 40, 0});
	pinhole_ptr->set_view_distance(400);  
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
	
	
	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->scale_radiance(0.90);
	emissive_ptr->set_ce(RGBColor{1.0});   			// white
		
	ConcaveSphere* sphere_ptr = new ConcaveSphere;
	sphere_ptr->set_radius(1000000.0);
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_shadows(false);
	add_object(sphere_ptr);
	
	EnvironmentLight* environment_light_ptr = new EnvironmentLight;
	environment_light_ptr->set_material(emissive_ptr);
	environment_light_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	environment_light_ptr->set_shadows(true);
//	add_light(environment_light_ptr);			// for Figure 18.7 (b) & (c)
		
	float const ka = 0.2;  	// common ambient reflection coefficient
	
	// large sphere
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20);
	sphere_ptr1->set_material(make_shared<Matte>(ka, .6, RGBColor{.75}));
	add_object(sphere_ptr1);
	
	// small sphere
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->set_material(make_shared<Matte>(ka, .5, RGBColor{.85}));
	add_object(sphere_ptr2);
	
	// medium sphere
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->set_material(make_shared<Matte>(ka, .5, RGBColor{.75}));
	add_object(sphere_ptr3);
	
	// cylinder
	float bottom 	= 0.0;
	float top 		= 85; 
	float radius	= 22;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(make_shared<Matte>(ka, .5, RGBColor{.60}));
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
