// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 26.8

#include "World.h"
#include "Tracers/PathTrace.h"
#include "Lights/Ambient.h"
#include "Cameras/Pinhole.h"
#include "Samplers/MultiJittered.h"
#include "Materials/Matte.h"
#include "Materials/Emissive.h"
#include "Materials/Reflective.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Rectangle.h"
#include "GeometricObjects/ConcaveSphere.h"
#include "GeometricObjects/SolidCylinder.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 100;  //5041;
	
	vp.set_hres(600);	  		
	vp.set_vres(400);
	vp.set_samples(num_samples); 
	vp.set_max_depth(5);
	
	tracer_ptr = new PathTrace(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({5, 10, 20});
	pinhole_ptr->set_lookat({-1, 1, 0});
	pinhole_ptr->set_view_distance(500);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	// emissive sphere
	
	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->scale_radiance(20.0); 
	emissive_ptr->set_ce({0.75, 1, 0.75});      // light green
		
	Sphere* sphere_ptr = new Sphere(Point3D(-2, 7, 6), 1); 
	sphere_ptr->set_material(emissive_ptr);
	sphere_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	add_object(sphere_ptr);
	
	
	// reflective rectangle
	
	auto reflective_ptr = make_shared<Reflective>();
	reflective_ptr->set_ka(0.0); 
	reflective_ptr->set_kd(0.0); 
	reflective_ptr->set_ks(0.0);    
	reflective_ptr->set_exp(1.0);
	reflective_ptr->set_kr(0.95); 
	reflective_ptr->set_cr(1.0, 0.5, 0.25);  // orange 	
	
	Point3D p0;
	Vector3D a, b;
	Normal normal;
	
	p0 = Point3D(-4.0, -1.0, 0.0);
	a = Vector3D(8.0, 0.0, 0.0);
	b = Vector3D(0.0, 20.0, 0.0);
	normal = Normal(0.0, 0.0, 1.0);
	Rectangle* mirror_ptr = new Rectangle(p0, a, b, normal);
	mirror_ptr->set_material(reflective_ptr);
	add_object(mirror_ptr);
		
	
	// plane

	auto matte_ptr = make_shared<Matte>();
	matte_ptr->set_ka(0);		
	matte_ptr->set_kd(0.75);
	matte_ptr->set_cd(white);
	matte_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	
	Plane* plane_ptr = new Plane(Point3D(0, -1.0, 0), Normal(0, 1, 0)); 	
	plane_ptr->set_material(matte_ptr);
	add_object(plane_ptr);
}
