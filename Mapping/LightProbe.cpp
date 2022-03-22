#include "Utilities/Constants.h"
#include "LightProbe.h"

LightProbe::LightProbe()
	: map_type{light_probe}
{}

void LightProbe::set_map_type(MapType type) {
	map_type = type;
}

void LightProbe::get_texel_coordinates(Point3D const & local_hit_point, int hres, int vres,
	int & row, int & column) const {

	float x = local_hit_point.x;
	float y = local_hit_point.y;
	float z = local_hit_point.z;

	float d = sqrt(x * x + y * y);
	float sin_beta = y / d;
	float cos_beta = x / d;
	float alpha;

	if (map_type == light_probe)   // the default
		alpha = acos(z);

	if (map_type == panoramic)
		alpha = acos(-z);

	float r = alpha * invPI<float>;
	float u = (1.0 + r * cos_beta) * 0.5;
	float v = (1.0 + r * sin_beta) * 0.5;
	column 	= (int) ((hres - 1) * u);
	row 	= (int) ((vres - 1) * v);
}

LightProbe::LightProbe(LightProbe const & rhs)
	: Mapping{rhs}
	, map_type{rhs.map_type}
{}

LightProbe * LightProbe::clone() const {
	return new LightProbe{*this};
}
