// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.25

// This scene illustrates fBm noise.
// The noise details are different from the images in the book.
// The noise is also lighter because the original noise functions didn't
// scale the values to lie in the interval [0,1].
// This build function renders them at 600 x 600 pixels, instead of the 
// original 150 x 150 pixels. 
// There is no antialiasing.

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Noise/CubicNoise.h"
#include "Textures/FBmTexture.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 1;
	
	vp.set_hres(600);    
	vp.set_vres(600);    
	vp.set_samples(num_samples);
	vp.set_gamut_display(true);
	
	background_color = black;
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 0, 100});
	pinhole_ptr->set_lookat(Point3D{0});
	pinhole_ptr->set_view_distance(6000.0); 
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1);		
	light_ptr->scale_radiance(2.5);
	add_light(light_ptr);
	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;	
	noise_ptr->set_num_octaves(6);		
//	noise_ptr->set_gain(0.0);				// for Figure 31.25(a) cubic noise - identical to Figure 31.21(a)
//	noise_ptr->set_gain(0.25);				// for Figure 31.25(b)
//	noise_ptr->set_gain(0.5);				// for Figure 31.25(c) fractal sum - similar to Figure 31.21(d)
//	noise_ptr->set_gain(0.75);				// for Figure 31.25(d)
	noise_ptr->set_gain(1.0);				// for Figure 31.25(e)
//	noise_ptr->set_gain(2.0);				// for Figure 31.25(f) new image - not in book
	noise_ptr->set_lacunarity(2.0);		
	
	// texture:

	FBmTexture* texture_ptr = new FBmTexture(noise_ptr);		
	texture_ptr->set_color(white);  
	texture_ptr->set_min_value(0.0);  
	texture_ptr->set_max_value(1.0);
	
	
	// material:
	
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	Plane* plane_ptr1 = new Plane(Point3D(0.0), Normal(0, 0, 1)); 
	plane_ptr1->set_material(sv_matte_ptr);
	add_object(plane_ptr1);
}
