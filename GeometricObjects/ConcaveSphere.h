#pragma once
#include "GeometricObject.h"
#include "Utilities/Point3D.h"
#include "Utilities/ShadeRec.h"
#include "Utilities/Ray.h"

class ConcaveSphere : public GeometricObject {
public:
	ConcaveSphere();
	ConcaveSphere(Point3D center, double r);
	void set_center(Point3D const & c);
	void set_radius(double r);
	bool hit(const Ray& ray, double& t, ShadeRec& s) const override;
	bool shadow_hit(Ray const & ray, double & tmin) const override;

	ConcaveSphere * clone() const override;
	ConcaveSphere& operator=(const ConcaveSphere& ConcaveSphere);

private:
	Point3D mCenter;
	double mRadius;

	static const double kEpsilon;
};
