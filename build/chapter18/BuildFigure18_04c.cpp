// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 18.4

#include "World/World.h"
#include "Tracers/AreaLighting.h"
#include "Samplers/MultiJittered.h"
#include "Cameras/Pinhole.h"
#include "Materials/Emissive.h"
#include "Materials/Matte.h"
#include "Lights/AreaLight.h"
#include "GeometricObjects/Rectangle.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
//	constexpr int num_samples = 1;   		// for Figure 18.4(a)
	constexpr int num_samples = 100;   	// for Figure 18.4(b) & (c)
	
//	Sampler* sampler_ptr = new MultiJittered(num_samples);

	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_sampler(make_unique<MultiJittered>(num_samples));

	background_color = RGBColor(0.5);

	tracer_ptr = new AreaLighting(this);

	auto camera = make_unique<Pinhole>();
	camera->set_eye({-20, 10, 20});
	camera->set_lookat({0, 2, 0});
	camera->set_view_distance(1080);          
	camera->compute_uvw();     
	set_camera(move(camera));

	// define a rectangle for the rectangular light
	
//	float width = 4.0;				// for Figure 18.4(a) & (b)
//	float height = 4.0;
	float width = 2.0;				// for Figure 18.4(c)
	float height = 2.0;
	Point3D center(0.0, 7.0, -7.0);	// center of each area light (rectangular, disk, and spherical)
	Point3D p0(-0.5 * width, center.y - 0.5 * height, center.z);
	Vector3D a(width, 0.0, 0.0);
	Vector3D b(0.0, height, 0.0);
	Normal normal(0, 0, 1);
	
	auto rectangle_ptr = make_unique<Rectangle>(p0, a, b, normal);
	rectangle_ptr->set_material(make_shared<Emissive>(white, 40.0));
	rectangle_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	rectangle_ptr->set_shadows(false);
//	add_object(rectangle_ptr);

	
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(move(rectangle_ptr));
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);
	
	
	// Four axis aligned boxes
		
	float box_width 	= 1.0; 		// x dimension
	float box_depth 	= 1.0; 		// z dimension
	float box_height 	= 4.5; 		// y dimension
	float gap			= 3.0; 
	
	auto matte_ptr1 = make_shared<Matte>(0.25, 0.75, RGBColor{0.4, 0.7, 0.4});
	
	Box* box_ptr0 = new Box(Point3D(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
							Point3D(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
	box_ptr0->set_material(matte_ptr1);
	add_object(box_ptr0);
	
	Box* box_ptr1 = new Box(Point3D(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
							Point3D(-0.5 * gap, box_height, 0.5 * box_depth)); 
	box_ptr1->set_material(matte_ptr1);
	add_object(box_ptr1);
		
	Box* box_ptr2 = new Box(Point3D(0.5 * gap, 0.0, -0.5 * box_depth), 
							Point3D(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->set_material(matte_ptr1);
	add_object(box_ptr2);
	
	Box* box_ptr3 = new Box(Point3D(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
							Point3D(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->set_material(matte_ptr1);
	add_object(box_ptr3);

	// ground plane
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
	plane_ptr->set_material(make_shared<Matte>(0.1, 0.9, white));
	add_object(plane_ptr);	
}
