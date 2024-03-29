// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This builds the scene for Figure 17.13 
// This is the city scene without the checker textures and rendered with
// an orthographoc camera

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Samplers/MultiJittered.h"
#include "Lights/AmbientOccluder.h"
#include "Lights/PointLight.h"
#include "Cameras/Orthographic.h"
#include "Cameras/Pinhole.h"
#include "Materials/Matte.h"
#include "GeometricObjects/Box.h"
#include "GeometricObjects/Plane.h"
#include "GeometricObjects/Grid.h"
#include "Utilities/Random.h"

using std::make_unique, std::make_shared, std::move;

void World::build() {
	constexpr int num_samples = 64;
	
	vp.set_hres(600);			
	vp.set_vres(400);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);	
	
	AmbientOccluder* ambient_occluder_ptr = new AmbientOccluder;
	ambient_occluder_ptr->set_sampler(make_unique<MultiJittered>(num_samples));
	ambient_occluder_ptr->set_min_amount(1.0);   	// for Figure 17.13(a)
//	ambient_occluder_ptr->set_min_amount(0.25);		// for Figure 17.13(b)
	set_ambient_light(ambient_occluder_ptr);
	
	
	auto camera = make_unique<Orthographic>();
	vp.set_pixel_size(0.31);
	camera->set_eye({100, 100, 50});
	camera->set_lookat({0, 10, 0});
	camera->compute_uvw();

	set_camera(move(camera));
	
	PointLight * light_ptr = new PointLight;
	light_ptr->set_location({150, 500, 300});
	light_ptr->scale_radiance(3.75);
	light_ptr->set_shadows(true);
	add_light(light_ptr);
	
	
	// city parameters
	
	float 	a					= 10;   // city block width:  xw extent
	float 	b   				= 12;	// city block length:  yw extent
	int 	num_rows			= 10;  	// number of blocks in the xw direction
	int 	num_columns			= 12; 	// number of blocks in the zw direction
	float	width				= 7;	// building width: xw extent in range [min, a - offset]
	float 	length				= 7;	// building length: zw extent in range [min, b - offset]
	float 	min_size			= 6;	// mininum building extent in xw and yw directions
	float 	offset				= 1.0;	// half the minimum distance between buildings
	float 	min_height			= 0.0; 	// minimum building height
	float 	max_height			= 30; 	// maximum bulding height
	float 	height;						// the building height in range [min_height, max_height]
	int		num_park_rows		= 4;  	// number of blocks of park in xw direction
	int		num_park_columns	= 6;  	// number of blocks of park in xw direction
	int 	row_test;					// there are no buildings in the park
	int 	column_test;				// there are no buildings in the park
	float 	min_color			= 0.1;  // prevents black buildings
	float 	max_color			= 0.9;	// prevents white buildings
		
	set_rand_seed(15);  				// as the buildings' dimensions and colors are random, it's necessary to 
										// seed rand to keep these quantities the same at each run
										// if you leave this out, and change the number of samples per pixel,
										// these will change
	
	// the buildings are stored in a grid
	
	Grid* grid_ptr = new Grid;
	
	for (int r = 0; r < num_rows; r++)  			// xw direction
		for (int c = 0; c < num_columns; c++) {		// zw direction
			// determine if the block is in the park
		
			if ((r - num_rows / 2) >= 0)
				row_test = r -  num_rows / 2;
			else
				row_test = r -  num_rows / 2 + 1;
				
			if ((c - num_columns / 2) >= 0)
				column_test = c - num_columns / 2;
			else
				column_test = c - num_columns / 2 + 1;
			
			if (abs(row_test) >= (num_park_rows / 2) || abs(column_test) >= (num_park_columns / 2)) {
		
				auto matte_ptr = make_shared<Matte>();
				matte_ptr->set_ka(0.4); 
				matte_ptr->set_kd(0.6);			
				matte_ptr->set_cd(RGBColor{
					min_color + rand_float() * (max_color - min_color),
					min_color + rand_float() * (max_color - min_color),
					min_color + rand_float() * (max_color - min_color)});
			
				// block center coordinates
				
				float xc = a * (r - num_rows / 2.0 + 0.5);
				float zc = b * (c - num_columns / 2.0 + 0.5);
				
				width = min_size + rand_float() * (a - 2 * offset - min_size);
				length = min_size + rand_float() * (b - 2 * offset - min_size);	
				
				// minimum building coordinates
				
				float xmin = xc - width / 2.0;
				float ymin = 0.0;
				float zmin = zc - length / 2.0;
				
				// maximum building coordinates
				
				height = min_height + rand_float() * (max_height - min_height);
				
				// The following is a hack to make the middle row and column of buildings higher
				// on average than the other buildings. 
				// This only works properly when there are three rows and columns of buildings
				
				if (r == 1 || r == num_rows - 2 || c == 1 || c == num_columns - 2)
					height *= 1.5;
				
				float xmax = xc + width / 2.0;
				float ymax = height;
				float zmax = zc + length / 2.0;
				
				Box* building_ptr = new  Box(Point3D(xmin, ymin, zmin), Point3D(xmax, ymax, zmax));
				building_ptr->set_material(matte_ptr);
				grid_ptr->add_object(building_ptr);
			}
		}
		
	grid_ptr->setup_cells();
	add_object(grid_ptr);
		
	// render the park green
	Box* park_ptr = new Box( 	Point3D(-a * num_park_rows / 2, 0.0, -b * num_park_columns / 2), 
								Point3D(a * num_park_rows / 2, 0.1, b * num_park_columns / 2)  );										
	park_ptr->set_material(make_shared<Matte>(.4, .5, RGBColor{.3, .5, .3}));
	add_object(park_ptr);
					
	
	// ground plane 
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->set_material(make_shared<Matte>(.3, .5, RGBColor{.85}));
	add_object(plane_ptr);
}
