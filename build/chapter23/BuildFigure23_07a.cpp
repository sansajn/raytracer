// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 23.7
// The two triangles are read from a PLY file
// The triangles can be flat or smooth shaded depending on which
// of the following two functions is called:

// Grid::grid_ptr->read_flat_triangles(file_name);
// Grid::grid_ptr->read_smooth_triangles(file_name);

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Grid.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);
	
	background_color = black;

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({100, 50, 90});
	pinhole_ptr->set_lookat({0, -0.5, 0});
	pinhole_ptr->set_view_distance(16000);  	
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
		
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(0.75, 1, -0.15);     
	directional_ptr->scale_radiance(4.5);  
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);
	
	const char* file_name = "assets/TwoTriangles.ply";
	Grid* grid_ptr = new Grid(new Mesh);
	grid_ptr->read_flat_triangles(file_name);		// for Figure 23.7(a)
//	grid_ptr->read_smooth_triangles(file_name);		// for Figure 23.7(b)
	grid_ptr->set_material(make_shared<Matte>(.1, .75, RGBColor{.1, .5, 1}));
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));  
	plane_ptr1->set_material(make_shared<Matte>(.25, .4, RGBColor{1, .9, .6}));
	add_object(plane_ptr1);	
}
