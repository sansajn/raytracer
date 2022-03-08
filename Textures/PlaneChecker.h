#pragma once
#include "Texture.h"

class PlaneChecker : public Texture {
public:
	PlaneChecker();

	void set_color1(RGBColor const & color);
	void set_color2(RGBColor const & color);
	void set_outline_color(RGBColor const & color);
	void set_size(float s);
	void set_outline_width(float ow);

	RGBColor get_color(ShadeRec const & sr) const override;

	// Copy API.
	PlaneChecker * clone() const override;

private:
	RGBColor _color1,
		_color2,
		_outline_color;
	float _size,
		_outline_width;
};
