// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Texture.h"
#include "Noise/LatticeNoise.h"

class FBmTexture: public Texture {			
public:
	FBmTexture() = default;
	FBmTexture(LatticeNoise*);
	void set_color(RGBColor c);
	void set_min_value(float);
	void set_max_value(float);
	RGBColor	get_color(const ShadeRec& sr) const override;

	FBmTexture * clone() const override;

private:
	LatticeNoise*		noise_ptr;
	RGBColor 	  		color;
	float		  		min_value, max_value;	// scaling factors
};

inline void 
FBmTexture::set_color(RGBColor c)
{
	this->color = c;
}

inline void 
FBmTexture::set_min_value(float a)
{
	min_value = a;
}
		
inline void
FBmTexture::set_max_value(float a)
{
	max_value = a;
}
