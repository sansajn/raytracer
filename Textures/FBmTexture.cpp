// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#include "Constants.h"
#include "FBmTexture.h"

// ---------------------------------------------------------------- copy constructor

FBmTexture::FBmTexture(LatticeNoise* n) {
	this->noise_ptr = n;
}


// ---------------------------------------------------------------- clone

FBmTexture*										
FBmTexture::clone(void) const {
	return (new FBmTexture(*this));
}	


// ---------------------------------------------------------------- destructor

RGBColor 														
FBmTexture::get_color(const ShadeRec& sr) const {

	float value = noise_ptr->value_fbm(sr.local_hit_point); // in the range (0, 1)
	value = min_value + (max_value - min_value) * value;	// in the range (min_value, max_value)
	
	/* NOTE: uncomment in case figure 31.18
	if (value < 0.0f || value > 1.0f)
		return red;
	*/

	return (value * color);
}
