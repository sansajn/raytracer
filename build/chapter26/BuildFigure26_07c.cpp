// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 26.7

#include "World.h"
#include "Tracers/PathTrace.h"
#include "Lights/Ambient.h"
#include "Cameras/Pinhole.h"
#include "Samplers/MultiJittered.h"
#include "Materials/Matte.h"
#include "Materials/Emissive.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Rectangle.h"
#include "GeometricObjects/ConcaveSphere.h"
#include "GeometricObjects/SolidCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
//	int num_samples = 1;		// for Figure 26.7(a)
//	int num_samples = 100;		// for Figure 26.7(b)
	int num_samples = 1024;		// for Figure 26.7(c)
//	int num_samples = 10000;	// for Figure 26.7(d)
		
	vp.set_hres(300);	  		
	vp.set_vres(300);
	vp.set_samples(num_samples); 
	vp.set_max_depth(10);
	
	background_color = black;
	
	tracer_ptr = new PathTrace(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({27.6, 27.4, -80.0});
	pinhole_ptr->set_lookat({27.6, 27.4, 0.0});
	pinhole_ptr->set_view_distance(400);      
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	Point3D p0;
	Vector3D a, b;
	Normal normal;
	
	// box dimensions
	
	double width 	= 55.28;   	// x direction
	double height 	= 54.88;  	// y direction
	double depth 	= 55.92;	// z direction
	
	
	// the ceiling light - doesn't need samples
	
	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->set_ce({1.0, 0.73, 0.4});
	emissive_ptr->scale_radiance(100);
	
	p0 = Point3D(21.3, height - 0.001, 22.7);
	a = Vector3D(0.0, 0.0, 10.5);
	b = Vector3D(13.0, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	Rectangle* light_ptr = new Rectangle(p0, a, b, normal);
	light_ptr->set_material(emissive_ptr);
	add_object(light_ptr);
	
		
	// left wall
	
	auto matte_ptr1 = make_shared<Matte>();
	matte_ptr1->set_ka(0.0);
	matte_ptr1->set_kd(0.6); 
	matte_ptr1->set_cd({0.57, 0.025, 0.025});	 // red
	matte_ptr1->set_sampler(make_unique<MultiJittered>(num_samples));
	
	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	Rectangle* left_wall_ptr = new Rectangle(p0, a, b, normal);
	left_wall_ptr->set_material(matte_ptr1);
	add_object(left_wall_ptr);
	
	
	// right wall
	
	auto matte_ptr2 = make_shared<Matte>();
	matte_ptr2->set_ka(0.0);
	matte_ptr2->set_kd(0.6); 
	matte_ptr2->set_cd({0.37, 0.59, 0.2});	 // green   from Photoshop
	matte_ptr2->set_sampler(make_unique<MultiJittered>(num_samples));
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	Rectangle* right_wall_ptr = new Rectangle(p0, a, b, normal);
	right_wall_ptr->set_material(matte_ptr2);
	add_object(right_wall_ptr);
	
	
	// back wall
	
	auto matte_ptr3 = make_shared<Matte>();
	matte_ptr3->set_ka(0.0);
	matte_ptr3->set_kd(0.6); 
	matte_ptr3->set_cd(white);
	matte_ptr3->set_sampler(make_unique<MultiJittered>(num_samples));
	
	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	Rectangle* back_wall_ptr = new Rectangle(p0, a, b, normal);
	back_wall_ptr->set_material(matte_ptr3);
	add_object(back_wall_ptr);
	
	
	// floor
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* floor_ptr = new Rectangle(p0, a, b, normal);
	floor_ptr->set_material(matte_ptr3);
	add_object(floor_ptr);
	
	
	// ceiling
	
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	Rectangle* ceiling_ptr = new Rectangle(p0, a, b, normal);
	ceiling_ptr->set_material(matte_ptr3);
	add_object(ceiling_ptr);

	
	// the two boxes defined as 5 rectangles each
	
	// short box
	
	// top
	
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* short_top_ptr = new Rectangle(p0, a, b, normal);
	short_top_ptr->set_material(matte_ptr3);
	add_object(short_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	Rectangle* short_side_ptr1 = new Rectangle(p0, a, b);
	short_side_ptr1->set_material(matte_ptr3);
	add_object(short_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	Rectangle* short_side_ptr2 = new Rectangle(p0, a, b);
	short_side_ptr2->set_material(matte_ptr3);
	add_object(short_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	Rectangle* short_side_ptr3 = new Rectangle(p0, a, b);
	short_side_ptr3->set_material(matte_ptr3);
	add_object(short_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	Rectangle* short_side_ptr4 = new Rectangle(p0, a, b);
	short_side_ptr4->set_material(matte_ptr3);
	add_object(short_side_ptr4);
	
	
	
	
	// tall box
	
	// top
	
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	Rectangle* tall_top_ptr = new Rectangle(p0, a, b, normal);
	tall_top_ptr->set_material(matte_ptr3);
	add_object(tall_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	Rectangle* tall_side_ptr1 = new Rectangle(p0, a, b);
	tall_side_ptr1->set_material(matte_ptr3);
	add_object(tall_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	Rectangle* tall_side_ptr2 = new Rectangle(p0, a, b);
	tall_side_ptr2->set_material(matte_ptr3);
	add_object(tall_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	Rectangle* tall_side_ptr3 = new Rectangle(p0, a, b);
	tall_side_ptr3->set_material(matte_ptr3);
	add_object(tall_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	Rectangle* tall_side_ptr4 = new Rectangle(p0, a, b);
	tall_side_ptr4->set_material(matte_ptr3);
	add_object(tall_side_ptr4);
}