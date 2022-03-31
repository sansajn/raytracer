// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// This builds the scenes for Figures 30.6(c) and (d)

#include "World/World.h"
#include "Tracers/RayCast.h"
#include "Cameras/Pinhole.h"
#include "Lights/Directional.h"
#include "Noise/CubicNoise.h"
#include "Textures/TInstance.h"
#include "Textures/TurbulenceTexture.h"
#include "Materials/SV_Matte.h"
#include "GeometricObjects/Box.h"

using std::make_unique, std::move, std::make_shared;

void World::build() {
	constexpr int num_samples = 16;
	
	vp.set_hres(600);
	vp.set_vres(600);
	vp.set_samples(num_samples);
	
	tracer_ptr = new RayCast(this);
	background_color = RGBColor(black);
			
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);    
	set_ambient_light(ambient_ptr);
	

	auto pinhole_ptr = make_unique<Pinhole>();
	pinhole_ptr->set_eye({0, 0, 100});
	pinhole_ptr->set_lookat(Point3D{0});
	pinhole_ptr->set_view_distance(30000.0); 
	pinhole_ptr->compute_uvw(); 
	set_camera(move(pinhole_ptr));
		
	Directional* light_ptr = new Directional;
	light_ptr->set_direction(0, 0, 1);  
	light_ptr->scale_radiance(3.0);   
	light_ptr->set_shadows(false);
	add_light(light_ptr);
	
	
	// turbulence texture
	
	// noise
	
	CubicNoise* noise_ptr = new CubicNoise;
	noise_ptr->set_num_octaves(1);
	noise_ptr->set_gain(0.5);	
	noise_ptr->set_lacunarity(2.0);
	
	// texture
	
	TurbulenceTexture* turbulence_texture_ptr = new TurbulenceTexture(noise_ptr);			
	turbulence_texture_ptr->set_color(1.0, 0.5, 0.0);  // orange 
	turbulence_texture_ptr->set_min_value(0.0);  
	turbulence_texture_ptr->set_max_value(1.2);
	
	float s = 0.05;      	// uniform scaling factor
	float xs = 10.0;		// non-uniform scaling factor in x direction
	TInstance* scaled_texture_ptr = new TInstance(turbulence_texture_ptr);
	scaled_texture_ptr->scale(s);				// for Figure 30.6(c)
//	scaled_texture_ptr->scale(s * xs, s, s);	// for Figure 30.6(d)
	
	// material:
		
	auto sv_matte_ptr = make_shared<SV_Matte>();
	sv_matte_ptr->set_ka(0.5);
	sv_matte_ptr->set_kd(0.85);
	sv_matte_ptr->set_cd(scaled_texture_ptr);
	
	
	// box parameters
	
	Point3D p0(-1.0);
	Point3D p1(1.0);
	
	Box* box_ptr = new Box(p0, p1); 
	box_ptr->set_material(sv_matte_ptr);
	add_object(box_ptr);	
}