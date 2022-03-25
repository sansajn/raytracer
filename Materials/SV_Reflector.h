// 	Copyright (C) Kevin Suffern 2000-2007.
//	Revised by mp77 at 2012
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "Phong.h"
#include "PerfectSpecular.h"
#include "Texture.h"
#include "SV_PerfectSpecular.h"

class SV_Reflector: public Phong {	
public:
	SV_Reflector();

	void set_kr(const float k);
	void set_cr(Texture* t_ptr);

	RGBColor shade(ShadeRec& s) const override;
	RGBColor area_light_shade(ShadeRec& sr) const override;		//This function doesn't appear in book, but needed by 24.43
	RGBColor path_shade(ShadeRec& sr) const override;

	virtual RGBColor global_shade(ShadeRec& sr);	 // FIXME: does not override

	// Copy API.
	SV_Reflector * clone() const override;
	SV_Reflector(const SV_Reflector& rm);
	SV_Reflector & operator= (const SV_Reflector& rhs);

	~SV_Reflector();

private:
	SV_PerfectSpecular* reflective_brdf;
	Texture *texture_ptr;
};


// ---------------------------------------------------------------- set_kr

inline void
SV_Reflector::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}

inline void
SV_Reflector::set_cr(Texture* c) {
	reflective_brdf->set_cr(c);
}
