#pragma once
#include "Mapping.h"

class CylindricalMap : public Mapping {
public:
	void get_texel_coordinates(
		const Point3D& localHitPoint,
		const int hres,
		const int vres,
		int& row,
		int& column
	) const override;

	CylindricalMap * clone() const override;
};
