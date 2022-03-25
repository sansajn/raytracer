#include "CylindricalMap.h"
#include "Utilities/Constants.h"

void CylindricalMap::get_texel_coordinates(const Point3D& localHitPoint, const int hres, const int vres, int& row, int& column) const {
	float phi = std::atan2(localHitPoint.x, localHitPoint.z);
	if (phi < 0.0f)
		phi += TWO_PI<float>;

	float u = phi * invTWO_PI<float>;
	float v = (static_cast<float>(localHitPoint.y) + 1.0f) / 2.0f;

	column = static_cast<int>((hres - 1) * u);
	row = static_cast<int>((vres - 1) * v);
}

CylindricalMap * CylindricalMap::clone() const {
	return new CylindricalMap{*this};
}
