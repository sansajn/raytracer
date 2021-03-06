#pragma once
#include "Materials/Material.h"
#include "Utilities/RGBColor.h"

class Emissive: public Material {	
public:
	Emissive();
	
	void scale_radiance(const float ls);
	void set_ce(RGBColor const & ce);

	RGBColor	shade(ShadeRec& sr) override;
	RGBColor	area_light_shade(ShadeRec& sr) override;
	RGBColor	get_Le(ShadeRec const & sr) const override;

	Material * clone() const override;
	Emissive(Emissive const & other);

private:

	float		ls;		// radiance scaling factor
	RGBColor 	ce;		// color

};
