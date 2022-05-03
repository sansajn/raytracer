#include "World/World.h"
#include "Samplers/MultiJittered.h"
#include "Cameras/Pinhole.h"
#include "Textures/Checker3D.h"
#include "Materials/SV_Matte.h"
#include "Materials/Emissive.h"
#include "Materials/Reflective.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Rectangle.h"
#include "Tracers/AreaLighting.h"
#include "Lights/AreaLight.h"
#include "Tracers/RayCast.h"

using std::make_unique, std::unique_ptr, std::make_shared;

void World::build(void) {
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_max_depth(1);

	constexpr int num_samples = 16;
	auto sampler_ptr = make_unique<MultiJittered>(num_samples);
	vp.set_sampler(move(sampler_ptr));

	tracer_ptr = new AreaLighting{this};

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({30, 13, 20});
	pinhole_ptr->set_lookat({0, -2, 0});
	pinhole_ptr->set_view_distance(12000); 
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));

	auto emissive_ptr = make_shared<Emissive>();
	emissive_ptr->scale_radiance(3.0);
	emissive_ptr->set_ce(white);

	auto area_light_sampler = make_unique<MultiJittered>(num_samples);
	
	Rectangle * rectangle_ptr = new Rectangle{Point3D{-1, -0.5, -1}, Vector3D{2, 0, 0}, Vector3D{0, 0, 2}, Normal{0, -1, 0}};
	rectangle_ptr->set_material(emissive_ptr);
	rectangle_ptr->set_sampler(move(area_light_sampler));
	add_object(rectangle_ptr);
	
	AreaLight * rectangularLight_ptr = new AreaLight;
	rectangularLight_ptr->set_object(unique_ptr<Rectangle>{rectangle_ptr->clone()});
	rectangularLight_ptr->set_shadows(true);
	add_light(rectangularLight_ptr);

	auto reflective_ptr1 = make_shared<Reflective>();
	reflective_ptr1->set_ka(0.2);
	reflective_ptr1->set_kd(0.1);
	reflective_ptr1->set_cd(RGBColor{0, 1, 0.2});  // green
	reflective_ptr1->set_ks(0.0);
	reflective_ptr1->set_exp(1);
	reflective_ptr1->set_kr(0.85);
	reflective_ptr1->set_cr(0.75, 0.75, 1);  // blue

	Sphere * sphere_ptr1 = new Sphere(Point3D(0, -2, 0), 0.5);
	sphere_ptr1->set_material(reflective_ptr1);
	add_object(sphere_ptr1);

	Checker3D * checker_ptr = new Checker3D;
	checker_ptr->set_size(1);		
	checker_ptr->set_color1(RGBColor{1.0});
	checker_ptr->set_color2(RGBColor{0.9});
	
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.75);
	sv_matte_ptr->set_cd(checker_ptr);
	
	Plane * plane_ptr = new Plane{Point3D{0, -2.75, 0}, Normal{0, 1, 0}};
	plane_ptr->set_material(sv_matte_ptr);
	add_object(plane_ptr);	
}
