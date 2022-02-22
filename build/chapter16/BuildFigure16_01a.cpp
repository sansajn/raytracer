// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 16.1

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Materials/Matte.h"
#include "Lights/Directional.h"
#include "Lights/PointLight.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Triangle.h"
#include "GeometricObjects/SolidCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	auto camera_ptr = make_unique<Pinhole>();
	camera_ptr->set_eye({2, 2.5, 15});
	camera_ptr->set_lookat({0 + 3, 2.5, 0});
	camera_ptr->set_view_distance(700);    
	camera_ptr->compute_uvw(); 
	set_camera(move(camera_ptr));
	
	Directional* light_ptr1 = new Directional();
	light_ptr1->set_direction(200, 150, 125); 
	light_ptr1->scale_radiance(4.0);
//	light_ptr1->set_shadows(true);				// for Figure 16.1(b)
	add_light(light_ptr1);
		
	PointLight* light_ptr2 = new PointLight();
	light_ptr2->set_location(-12, 15, 30); 
	light_ptr2->scale_radiance(4.0);
//	light_ptr2->set_shadows(true);				// for Figure 16.1(b)
	add_light(light_ptr2);
		
	// sphere
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0.0, 2.4, 0), 1.5); 
	sphere_ptr1->set_material(make_shared<Matte>(.3, .3, RGBColor{.5, .6, 0}));
	add_object(sphere_ptr1);	
	
	// box
	
	auto mate_ptr2 = make_shared<Matte>(.2, .3, RGBColor{.8, .5, 0});

	Box* box_ptr1 = new Box(Point3D(5.4, -0.5, -3), Point3D(7.5, 4.75, 0.60));
	box_ptr1->set_material(mate_ptr2);
	add_object(box_ptr1);
		
	// triangle

	Triangle* triangle_ptr1 = new Triangle(	Point3D(1.5, -0.5, 1.8), 		// front
											Point3D(7.5, -0.5, -9.00), 		// back
											Point3D(2.35, 5.8, 1.4));		// top									
	triangle_ptr1->set_material(make_shared<Matte>(.35, .5, RGBColor{0, .5, .5}));
	add_object(triangle_ptr1);
		
	// cylinder
	
	float bottom 	= -0.5;
	float top 		= 1.0;
	float radius 	= 1.0;

	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(mate_ptr2);
	add_object(cylinder_ptr);

	// ground plane
	Plane* plane_ptr = new Plane(Point3D(0, -0.5, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.1, .2, white));
	add_object(plane_ptr);
}
