// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 17.12
// Triangle meshes are discussed in Chapter 23
// The bunny PLY files are in the Chapter 23 archive

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Samplers/MultiJittered.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/Directional.h"
#include "Cameras/Pinhole.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Rectangle.h"


using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 256;
	
	vp.set_hres(400);
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	
	auto sampler_ptr = make_unique<MultiJittered>(num_samples);
	
	AmbientOccluder* acl_ptr = new AmbientOccluder;
	acl_ptr->set_min_amount(1.0);    	// for Figure 17.12(a)
//	acl_ptr->set_min_amount(0.25);		// for Figure 17.12(b)
//	acl_ptr->set_min_amount(0.0);		// for Figure 17.12(c)
	acl_ptr->set_sampler(move(sampler_ptr));
	set_ambient_light(acl_ptr);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	
	// for regular view	
	
	pinhole_ptr->set_eye({20, 10, 40});
	pinhole_ptr->set_lookat({-0.025, 0.11, 0.0});
	pinhole_ptr->set_view_distance(70000);	
	pinhole_ptr->compute_uvw();
	set_camera(move(pinhole_ptr));
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->set_direction(20, 40, 20);
	light_ptr1->scale_radiance(1.5); 
	light_ptr1->set_shadows(true);
	add_light(light_ptr1);

	
	float ka = 0.5;		// used for all materials

	auto matte_ptr1 = make_shared<Matte>();
	matte_ptr1->set_ka(ka);
	matte_ptr1->set_kd(0.5);
	matte_ptr1->set_cd(pale_blue);   // pale blue for bunny

	const char* file_name = "assets/bunny.ply"; 	// 10000 triangles - needs the normals reversed
	
	auto bunny_ptr = make_shared<Grid>();
	bunny_ptr->reverse_mesh_normals();				// only required for the Bunny10K.ply file
//	bunny_ptr->read_flat_triangles(file_name);		// read PLY file
	bunny_ptr->read_smooth_triangles(file_name);	// read PLY file
	bunny_ptr->set_material(matte_ptr1);
	bunny_ptr->setup_cells();
	
	Instance* rotated_bunny_ptr = new Instance{bunny_ptr};
	rotated_bunny_ptr->set_material(matte_ptr1);
	rotated_bunny_ptr->rotate_y(40);
	add_object(rotated_bunny_ptr);
	
	
	// rectangle parameters
	
	Point3D p0(-0.13, 0.033, -0.1);  	// common corner
	float height = 0.25;  				// y direction
	float width = 0.45;  				// x direction	
	float depth = 0.45;   				// z direction	

	// horizontal rectangle 
	
	Rectangle* rectangle_ptr1 = new Rectangle(p0, Vector3D(0, 0,depth), Vector3D(width, 0, 0));
	rectangle_ptr1->set_material(make_shared<Matte>(ka, .5, white));
	add_object(rectangle_ptr1);	
	
	// rectangle perpendicular to x axis
	Rectangle* rectangle_ptr2 = new Rectangle(p0, Vector3D(0, height, 0), Vector3D(0, 0, depth));
	rectangle_ptr2->set_material(make_shared<Matte>(ka, .75, RGBColor{.5, 1, .75}));
	add_object(rectangle_ptr2);	
	
	// rectangle perpendicular to w axis
	Rectangle* rectangle_ptr3 = new Rectangle(p0, Vector3D(width, 0, 0), Vector3D(0, height, 0));
	rectangle_ptr3->set_material(make_shared<Matte>(ka, .5, RGBColor{1, 1, .5}));
	add_object(rectangle_ptr3);
}
