#pragma once
#include "Materials/Material.h"
#include "Utilities/RGBColor.h"

class Emissive: public Material {	
public:
	Emissive();
	Emissive(RGBColor const & ce, float ls = 1.0f);
	
	void scale_radiance(const float ls);
	void set_ce(RGBColor const & ce);

	RGBColor	shade(ShadeRec& sr) const override;
	RGBColor	area_light_shade(ShadeRec& sr) const override;
	RGBColor path_shade(ShadeRec & sr) const override;
	RGBColor	get_Le(ShadeRec const & sr) const override;

	Material * clone() const override;

private:
	float	ls;  //!< radiance scaling factor
	RGBColor ce;  //!< color
};
