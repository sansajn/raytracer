#pragma once
#include "RGBColor.h"
#include "ShadeRec.h"

class Material {	
public:
	Material() = default;

	virtual RGBColor shade(ShadeRec & sr) const;
	virtual RGBColor area_light_shade(ShadeRec & sr) const;  // TODO: to support what?
	virtual RGBColor path_shade(ShadeRec & sr) const;  //!< To support *path tracing*, \sa PathTrace
	virtual RGBColor get_Le(ShadeRec const & sr) const;

	// Copy API.
	virtual Material * clone(void) const = 0;
	Material(Material const & material) = default;

	virtual ~Material() = default;

protected:
	Material & operator=(Material const & rhs) = default;
};
