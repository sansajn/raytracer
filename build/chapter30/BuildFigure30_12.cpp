// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 30.12

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Noise/CubicNoise.h"
#include "Textures/TInstance.h"
#include "Textures/Checker3D.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/SolidCylinder.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(904);	  		
	vp.set_vres(300);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(0.5);	
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 125, 200});
	pinhole_ptr->set_lookat(Point3D{0});
	pinhole_ptr->set_view_distance(4400.0);  
	pinhole_ptr->compute_uvw();  
	set_camera(move(pinhole_ptr));
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(1, 1, 0.5); 
	light_ptr->scale_radiance(4.5);
	add_light(light_ptr);
	
	
	// middle cylinder (generic)
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->set_size(1.02); 
	checker_ptr->set_color1(black);
	checker_ptr->set_color2(white);
	 
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.4);  
	sv_matte_ptr->set_kd(0.6);
	sv_matte_ptr->set_cd(checker_ptr);
	
	SolidCylinder* cylinder_ptr1 = new SolidCylinder;
	cylinder_ptr1->set_material(sv_matte_ptr);
	add_object(cylinder_ptr1);
	
	
	// right cylinder (cylinder and checkers are transformed)
	
	Instance* transformed_cylinder_ptr1 = new Instance(make_shared<SolidCylinder>());
	transformed_cylinder_ptr1->set_material(sv_matte_ptr);
	transformed_cylinder_ptr1->scale({10.0, 0.5, 10.0});
	transformed_cylinder_ptr1->translate({13, 0, 0});
	add_object(transformed_cylinder_ptr1);
	
	
	// left cylinder (only the cylinder is transformed)
	
	Instance* transformed_cylinder_ptr2 = new Instance(make_shared<SolidCylinder>());
	transformed_cylinder_ptr2->set_material(sv_matte_ptr);
	transformed_cylinder_ptr2->scale({10.0, 0.5, 10.0});
	transformed_cylinder_ptr2->translate({-13, 0, 0});
	transformed_cylinder_ptr2->transform_texture(false);
	add_object(transformed_cylinder_ptr2);
}
