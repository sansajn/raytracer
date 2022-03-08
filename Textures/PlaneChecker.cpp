#include "Utilities/Constants.h"
#include "PlaneChecker.h"

PlaneChecker::PlaneChecker()
	: _color1{black}
	, _color2{white}
	, _outline_color{black}
	, _outline_width{0.0}
	, _size{1.0}
{}

void PlaneChecker::set_color1(RGBColor const & color) {
	_color1 = color;
}

void PlaneChecker::set_color2(RGBColor const & color) {
	_color2 = color;
}

void PlaneChecker::set_outline_color(const RGBColor& color) {
	_outline_color = color;
}

void PlaneChecker::set_size(float s) {
	_size = s;
}

void PlaneChecker::set_outline_width(float ow) {
	_outline_width = ow;
}

PlaneChecker * PlaneChecker::clone() const {
	return new PlaneChecker{*this};
}

RGBColor PlaneChecker::get_color(ShadeRec const & sr) const {
	float x = sr.local_hit_point.x;
	float z = sr.local_hit_point.z;
	int ix = std::floor(x / _size);
	int iz = std::floor(z / _size);
	float fx = x / _size - ix;
	float fz = z / _size - iz;
	float width = 0.5 * _outline_width / _size;
	bool isInOutline = (fx < width || fx > 1.0 - width) || (fz < width || fz > 1.0 - width);

	if (isInOutline)
		return _outline_color;

	if ((ix + iz) % 2 == 0)
		return _color1;
	else
		return _color2;
}
