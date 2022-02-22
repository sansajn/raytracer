// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 22.09

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Orthographic.h"
#include "Lights/Directional.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Grid.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);

	auto orthographic_ptr = make_unique<Orthographic>();
	vp.set_pixel_size(0.0085);
	orthographic_ptr->set_eye({7, 5, 5});
	orthographic_ptr->set_lookat({0, 0, 0});
	orthographic_ptr->compute_uvw(); 
	set_camera(move(orthographic_ptr));
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(1, 0, 0);    				// from the +ve x direction     
	light_ptr1->scale_radiance(1);   
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->set_direction(0, 1, 0);    				// from the +ve y direction     
	light_ptr2->scale_radiance(2);   
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);	
	
	Directional* light_ptr3 = new Directional;
	light_ptr3->set_direction(0, 0, 1);    				// from the +ve z direction      
	light_ptr3->scale_radiance(1.5);   
	light_ptr3->set_shadows(true);
	add_light(light_ptr3);
	
	Directional* light_ptr4 = new Directional;
	light_ptr4->set_direction(-1, 0, 0);    			// from the -ve x direction     
	light_ptr4->scale_radiance(1);   
	light_ptr4->set_shadows(true);
	add_light(light_ptr4);
	
	Directional* light_ptr5 = new Directional;
	light_ptr5->set_direction(0, -1, 0);    			// from the -ve y direction     
	light_ptr5->scale_radiance(2);   
	light_ptr5->set_shadows(true);
	add_light(light_ptr5);	
	
	Directional* light_ptr6 = new Directional;
	light_ptr6->set_direction(0, 0, -1);    			// from the -ve z direction      
	light_ptr6->scale_radiance(1.5);   
	light_ptr6->set_shadows(true);
	add_light(light_ptr6);
	
	
	Grid* grid_ptr = new Grid;

	// eight boxes
	
	// bottom four
	
	float bottom_size = 0.5;
	Vector3D diagonal(bottom_size, bottom_size, bottom_size);
	Point3D p0;
	
	p0 = Point3D(-1, -1, -1);
	Box* box_ptr1 = new Box(p0, p0 + diagonal); 
	box_ptr1->set_material(make_shared<Matte>(.25, .75, gray));
	grid_ptr->add_object(box_ptr1);
		
	p0 = Point3D(-1, -1, 1 - bottom_size);
	Box* box_ptr2 = new Box(p0, p0 + diagonal); 
	box_ptr2->set_material(make_shared<Matte>(.25, .75, red));
	grid_ptr->add_object(box_ptr2);
	
	p0 = Point3D(1 - bottom_size, -1, 1 - bottom_size);
	Box* box_ptr3 = new Box(p0, p0 + diagonal); 
	box_ptr3->set_material(make_shared<Matte>(.25, .75, yellow));
	grid_ptr->add_object(box_ptr3);
	
	p0 = Point3D(1 - bottom_size, -1, -1);
	Box* box_ptr4 = new Box(p0, p0 + diagonal); 
	box_ptr4->set_material(make_shared<Matte>(.25, .75, RGBColor{.2, .6, .4}));
	grid_ptr->add_object(box_ptr4);
	
	
	// top four
	
	float top_size = 0.35;
	diagonal = Vector3D(top_size, top_size, top_size);
	
	p0 = Point3D(-1, 1 - top_size, -1);
	Box* box_ptr5 = new Box(p0, p0 + diagonal); 
	box_ptr5->set_material(make_shared<Matte>(.25, .75, RGBColor{.27, .36, 1}));
	grid_ptr->add_object(box_ptr5);

	p0 = Point3D(-1, 1 - top_size, 1 - top_size);
	Box* box_ptr6 = new Box(p0, p0 + Vector3D(0.25, top_size, top_size)); 
	box_ptr6->set_material(make_shared<Matte>(.25, .75, majenta));
	grid_ptr->add_object(box_ptr6);
	
	p0 = Point3D(1 - 0.25, 1 - 0.25, 1 - 0.25);
	Box* box_ptr7 = new Box(p0, p0 + Vector3D(0.25)); 
	box_ptr7->set_material(make_shared<Matte>(.25, .75, white));
	grid_ptr->add_object(box_ptr7);
	
	p0 = Point3D(1 - top_size, 1 - top_size, -1);
	Box* box_ptr8 = new Box(p0, p0 + Vector3D(top_size, top_size, 0.25)); 
	box_ptr8->set_material(make_shared<Matte>(.25, .75, RGBColor{0, .75, .75}));
	grid_ptr->add_object(box_ptr8);
	
	grid_ptr->setup_cells();
	add_object(grid_ptr);
}
