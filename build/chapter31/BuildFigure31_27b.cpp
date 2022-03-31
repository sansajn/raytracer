// 	Copyright (C) Kevin Suffern 2000-2008.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scene for Figure 31.27(b).

// The sphere in this image is twice the size of the spheres in Figures 31.27(b) and 31.27(c).
// This is now rendered with a gray background.

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/PointLight.h"
#include "Noise/CubicNoise.h"
#include "Textures/FBmTexture.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Plane.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	vp.set_hres(600);    
	vp.set_vres(600);
	vp.set_samples(num_samples);
	vp.set_gamut_display(true);
	
	background_color = RGBColor(0.5);
	tracer_ptr = new RayCast(this);
	
	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 0, 100});
	pinhole_ptr->set_lookat(Point3D{0});
	pinhole_ptr->set_view_distance(9500);
	pinhole_ptr->compute_uvw();     
	set_camera(move(pinhole_ptr));
	
	
	PointLight* light_ptr = new PointLight;
	light_ptr->set_location({10, 10, 20});
	light_ptr->scale_radiance(3.5);
	add_light(light_ptr);
	
	
	// noise:
	
	CubicNoise* noise_ptr = new CubicNoise;
	noise_ptr->set_num_octaves(6);
	noise_ptr->set_gain(.5);			// not relevant when num_octaves = 1
	noise_ptr->set_lacunarity(2);     // not relevant when num_octaves = 1
	
	// texture:		
	
	FBmTexture* texture_ptr = new FBmTexture(noise_ptr);			
	texture_ptr->set_color(light_blue);
	texture_ptr->set_min_value(0.0);  
	texture_ptr->set_max_value(1.0);

	// material:
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.25);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(texture_ptr);
	
	// the sphere:
	
	Sphere* sphere_ptr = new Sphere(Point3D{0}, 3);
	sphere_ptr->set_material(sv_matte_ptr);
	add_object(sphere_ptr);
}