#include "CylindricalMap.h"
#include "Utilities/Constants.h"

void CylindricalMap::get_texel_coordinates(const Point3D& localHitPoint, const int hres, const int vres, int& row, int& column) const {
	float phi = std::atan2(localHitPoint.x, localHitPoint.z);
	if (phi < 0.0)
		phi += TWO_PI<float>;

	float u = phi * invTWO_PI<float>;
	float v = (localHitPoint.y + 1) / 2;

	row = static_cast<int>((hres - 1) * u);
	column = static_cast<int>((vres - 1) * v);
}

CylindricalMap * CylindricalMap::clone() const {
	return new CylindricalMap{*this};
}
