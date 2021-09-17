#pragma once
#include "RGBColor.h"
#include "ShadeRec.h"

class Material {	
public:
	Material() = default;

	virtual RGBColor shade(ShadeRec & sr);
	virtual RGBColor area_light_shade(ShadeRec & sr);
	virtual RGBColor get_Le(ShadeRec const & sr) const;

	virtual Material * clone(void) const = 0;
	Material(Material const & material) = default;

	virtual ~Material() = default;

protected:
	Material & operator=(Material const & rhs);
};
