// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 29.22

// The two triangles are read from a ply file.
// The triangles can be flat or smooth shaded depending on which of the 
// following two functions is called:

// Grid::grid_ptr->read_flat_uv_triangles(file_name);
// Grid::grid_ptr->read_smooth_uv_riangles(file_name);

// The version of the Grid class in the Chapter 29 download includes these functions, and the 
// function Grid::read_uv_ply_file, which they call.

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Utilities/Image.h"
#include "Textures/ImageTexture.h"
#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Grid.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(400);      
	vp.set_vres(400);    
	vp.set_samples(num_samples);	
	
	tracer_ptr = new RayCast(this);
	
	background_color = black;

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({11, 5, 9});
	pinhole_ptr->set_view_distance(1600.0);
	pinhole_ptr->set_lookat({0, -0.5, 0});
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	Directional* directional_ptr = new Directional;
	directional_ptr->set_direction(0.75, 1, -0.15);     
	directional_ptr->scale_radiance(4.5); 
	directional_ptr->set_shadows(true);
	add_light(directional_ptr);
	
	Image* image_ptr = new Image;						
	image_ptr->read_ppm_file("assets/BlueGlass.ppm");
	
	ImageTexture* texture_ptr = new ImageTexture; 
	texture_ptr->set_image(image_ptr);

	const char* file_name = "assets/TwoUVTriangles.ply";
	Grid* grid_ptr = new Grid(new Mesh);
//	grid_ptr->read_flat_uv_triangles(file_name);		// for Figure 29.22(a)
	grid_ptr->read_smooth_uv_triangles(file_name);		// for Figure 29.22(b)
	grid_ptr->set_material(make_shared<SV_Matte>(.1, .75, texture_ptr));
	grid_ptr->setup_cells();
	add_object(grid_ptr);
	
	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));  
	plane_ptr1->set_material(make_shared<Matte>(.25, .4, RGBColor{1, .9, .6}));
	add_object(plane_ptr1);	
}
