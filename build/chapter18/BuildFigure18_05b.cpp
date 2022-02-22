// This builds the scene for Figure 18.5(a)

#include "World/World.h"
#include "Samplers/MultiJittered.h"
#include "Tracers/AreaLighting.h"
#include "Cameras/Pinhole.h"
#include "Materials/Emissive.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Sphere.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "Lights/AreaLight.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 100;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_max_depth(0);
	vp.set_sampler(make_unique<MultiJittered>(num_samples));

	background_color = RGBColor(0.5);

	tracer_ptr = new AreaLighting(this);

	auto camera = make_unique<Pinhole>();
	camera->set_eye({-20, 10, 20});
	camera->set_lookat({0, 2, 0});
	camera->set_view_distance(1080);          
	camera->compute_uvw();     
	set_camera(move(camera));

	
	// disk for the disk light
	
	Point3D center(0.0, 7.0, -7.0);
	float width = 4.0;
	float radius = 0.56 * width;
	
	auto sphere_ptr = make_unique<Sphere>(center, radius);
	sphere_ptr->set_material(make_shared<Emissive>(white, 40));
	sphere_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	sphere_ptr->set_shadows(false);
//	disk_ptr->compute_uvw();
//	add_object(disk_ptr);
	
	AreaLight* area_light_ptr = new AreaLight;
	area_light_ptr->set_object(move(sphere_ptr));
	area_light_ptr->set_shadows(true);
	add_light(area_light_ptr);
	
	
	// Four axis aligned boxes
		
	float box_width 	= 1.0; 		// x dimension
	float box_depth 	= 1.0; 		// z dimension
	float box_height 	= 4.5; 		// y dimension
	float gap			= 3.0; 
	
	auto matte_ptr1 = make_shared<Matte>(.25, .75, RGBColor{0.4, 0.7, 0.4});
	
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
	
	auto matte_ptr2 = make_shared<Matte>(.1, .90, white);
		
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0)); 
	plane_ptr->set_material(matte_ptr2);
	add_object(plane_ptr);	
}
