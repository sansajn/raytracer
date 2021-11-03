/*! \file
Catch approximation helpers for the math library. */
#pragma once
#include <catch.hpp>
#include "Utilities/Vector3D.h"

class approx_vec3 {
public:
	explicit approx_vec3(Vector3D const & v)
		: _v{v}
		, _eps{std::numeric_limits<double>::epsilon()}
	{}

	bool operator==(Vector3D const & rhs) const {
		return _v.x == Approx{rhs.x}.epsilon(_eps) && _v.y == Approx{rhs.y}.epsilon(_eps)
			&& _v.z == Approx{rhs.z}.epsilon(_eps);
	}

	std::string toString() const {
		std::ostringstream o;
		o << "Approx( " << Catch::toString(_v) << " )";
		return o.str();
	}

private:
	Vector3D _v;
	double _eps;
};

namespace Catch {

template<>
inline std::string toString<approx_vec3>(approx_vec3 const & value) {
	 return value.toString();
}

}  // Catch

bool operator==(Vector3D const & lhs, approx_vec3 const & rhs) {
	return rhs == lhs;
}
