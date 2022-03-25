// 	Copyright (C) Mp77 2012
//	Original from Kevin Suffern 2000-2007
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

#include "RGBColor.h"
#include "Material.h"
#include "Texture.h"

class SV_Emissive: public Material {	
private:
	
	float		ls;		// radiance scaling factor
	RGBColor 	ce;		// color
	
public:
	SV_Emissive(void);

	RGBColor	shade(ShadeRec & sr) const override;
	void scale_radiance(const float _ls);
	void set_ce(const float r, const float g, const float b);
	void set_ce(RGBColor);
	void set_ce(Texture *t);

	RGBColor get_Le(ShadeRec const & sr) const override;
	RGBColor area_light_shade(ShadeRec & sr) const override;

	virtual RGBColor global_shade(ShadeRec& sr);  // FIXME: global_shade not implemented in Material

	RGBColor	path_shade(ShadeRec & sr) const override;

	// Copy API.
	SV_Emissive * clone() const override;
	SV_Emissive(const SV_Emissive& material);
	virtual SV_Emissive & operator=(const SV_Emissive& rhs);


	virtual ~SV_Emissive(void);


private:
	Texture* t;

};
