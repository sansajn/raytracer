// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 14.7

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Materials/Matte.h"
#include "GeometricObjects/SolidCylinder.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build(){
	constexpr int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
			
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
	
	float a = 0.75;
	background_color = RGBColor(0.0, 0.3 * a, 0.25 * a);  // torquise
			
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye(7.5, 4, 10); 
	pinhole_ptr->set_lookat(-1, 3.7, 0);  
	pinhole_ptr->set_view_distance(340);		
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(15, 15, 2.5); 
	light_ptr->scale_radiance(2.0);	
	add_light(light_ptr);
		
	
	// spheres
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(3.85, 2.3, -2.55), 2.3);
	sphere_ptr1->set_material(make_shared<Matte>(0.25, 0.75, RGBColor{0.75, 0.75, 0}));
	add_object(sphere_ptr1);
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-0.7, 1, 4.2), 2);
	sphere_ptr2->set_material(make_shared<Matte>(0.45, 0.75, RGBColor{0.75, 0.25, 0}));
	add_object(sphere_ptr2);

	// cylinder 
	
	float bottom 	= 0.0;
	float top 		= 8.5;   
	float radius	= 2.2;
	SolidCylinder* cylinder_ptr = new SolidCylinder(bottom, top, radius);
	cylinder_ptr->set_material(make_shared<Matte>(0.4, 0.75, RGBColor{1, 0.5, 1}));
	add_object(cylinder_ptr);
	
	// box
		
	Box* box_ptr = new Box(Point3D(-3.5, 0, -11), Point3D(-2.5, 6, 6.5));
	box_ptr->set_material(make_shared<Matte>(0.15, 0.5, RGBColor{0.75, 1.0, 0.75}));
	add_object(box_ptr);
	
	// ground plane
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(0.2, 0.97, white));
	add_object(plane_ptr);
}
