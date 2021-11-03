// `Instance` sample
#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Materials/Matte.h"
#include "Materials/Phong.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Box.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);	
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);
		
	tracer_ptr = new RayCast(this);
	
	auto pinHole_ptr = make_unique<Pinhole>();
	pinHole_ptr->set_eye(7.7, 6, 15);
	pinHole_ptr->set_lookat(-1.0, -0.5, 0); 
	pinHole_ptr->set_view_distance(650);
	pinHole_ptr->compute_uvw();
	set_camera(move(pinHole_ptr));
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->set_location(30, 30, 25); 
	light_ptr1->set_location(30, 20, -10);  
	light_ptr1->scale_radiance(2.5);  
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);
	
	PointLight* light_ptr2 = new PointLight;
	light_ptr2->set_location(10, 20, 40);  
	light_ptr2->scale_radiance(1.5);  
	light_ptr2->set_shadows(true);
	add_light(light_ptr2);
	
	// ground plane 
	
	Plane* planePr1 = new Plane(Point3D(0, 0.24, 0), Normal(0, 1, 0));
	planePr1->set_material(make_shared<Matte>(0.35, 0.75, white));
	add_object(planePr1);

	auto box = make_shared<Box>(Point3D{0, 0, 0}, Point3D{1, 1, 1});

	Instance * inst = new Instance{box};
	inst->set_material(make_shared<Matte>(0.5, 0.5, RGBColor{0, 0.5, 0.5}));
	inst->scale(Vector3D{2.0});
	inst->translate(Vector3D{-1, 0, 0});
	inst->compute_bounding_box();
	add_object(inst);
}
