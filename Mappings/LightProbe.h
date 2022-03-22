#pragma once
#include "Mapping.h"

typedef enum {
	light_probe,
	panoramic
} MapType;


class LightProbe : public Mapping {
public:
	LightProbe();
	void set_map_type(MapType type);

	void get_texel_coordinates(Point3D const & local_hit_point, int hres, int vres,
		int & row, int & column) const override;

	LightProbe(LightProbe const & rhs);
	LightProbe * clone() const override;

private:
	MapType map_type;
};
