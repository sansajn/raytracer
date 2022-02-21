// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 21.5(b)

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/Phong.h"
#include "GeometricObjects/Instance.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>(Point3D{100, 0, 100}, Point3D{0,1,0}, 8000);
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));

	PointLight* light_ptr = new PointLight;
	light_ptr->set_location(50, 50, 1);
	light_ptr->scale_radiance(3.0);   
	add_light(light_ptr);
	
	auto phong_ptr = make_shared<Phong>();
	phong_ptr->set_cd(RGBColor{0.75});
	phong_ptr->set_ka(0.25);
	phong_ptr->set_kd(0.8);
	phong_ptr->set_ks(0.15);
	phong_ptr->set_exp(50.0);  
	
	Instance* ellipsoid_ptr = new Instance(make_shared<Sphere>());
	ellipsoid_ptr->set_material(phong_ptr);
	ellipsoid_ptr->scale(Vector3D{2,3,1});
	ellipsoid_ptr->rotate_x(-45);
	ellipsoid_ptr->translate(Vector3D{0,1,0});
	add_object(ellipsoid_ptr);
}
