#include "ConcaveSphere.h"
#include <cmath>

const double ConcaveSphere::kEpsilon = 0.001;

ConcaveSphere::ConcaveSphere()
	: mCenter(0.0)
	, mRadius(1.0)
{}

ConcaveSphere::ConcaveSphere(Point3D center, double r)
	: GeometricObject()
	, mCenter(center)
	, mRadius(r)
{}

ConcaveSphere& ConcaveSphere::operator=(const ConcaveSphere& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}

	GeometricObject::operator=(rhs);
	mCenter = rhs.mCenter;
	mRadius = rhs.mRadius;

	return (*this);
}

ConcaveSphere * ConcaveSphere::clone() const {
	return new ConcaveSphere{*this};
}

void ConcaveSphere::set_center(const Point3D& c) {
	mCenter = c;
}

void ConcaveSphere::set_radius(double r) {
	mRadius = r;
}

bool ConcaveSphere::hit(const Ray& ray, double& tMin, ShadeRec& sr) const {
	double t;
	Vector3D temp = ray.o - mCenter; //direction vector for Sphere. (o - c)
	double a = ray.d * ray.d;
	double b = 2.0 * temp * ray.d; // b = 2(o - c) * d
	double c = temp * temp - mRadius * mRadius; // c = (o - c) * (o - c) - r * r;
	double disc = b * b - 4.0 * a * c; // discriminant

	if (disc < 0.0) // No hit
	{
		return false;
	}
	else // one or two hit
	{
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;  //swaller root

		if (t > kEpsilon) {
			tMin = t;
			sr.normal = -(temp + t * ray.d) / mRadius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon) {
			tMin = t;
			sr.normal = -(temp + t * ray.d) / mRadius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}
	}
	return false;
}

bool ConcaveSphere::shadow_hit(Ray const & ray, double & tMin) const {
	if (!casts_shadows())
		return false;

	double t;
	Vector3D temp = ray.o - mCenter; //direction vector for Sphere. (o - c)
	double a = ray.d * ray.d;
	double b = 2.0 * temp * ray.d; // b = 2(o - c) * d
	double c = temp * temp - mRadius * mRadius; // c = (o - c) * (o - c) - r * r;
	double disc = b * b - 4.0 * a * c; // discriminant

	if (disc < 0.0) // No hit
	{
		return false;
	}
	else // one or two hit
	{
		double e = std::sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;  //swaller root

		if (t > kEpsilon) {
			tMin = t;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon) {
			tMin = t;
			return true;
		}
	}
	return false;
}
