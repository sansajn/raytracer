// This file contains the definition of the class sphere

#include "Sphere.h"
#include "Utilities/Maths.h"

const double Sphere::kEpsilon = 0.001;
					
// ---------------------------------------------------------------- default constructor

Sphere::Sphere()
	: _center{0}
	, _radius{1.0}
	, _inv_area{0}
{}


// ---------------------------------------------------------------- constructor

Sphere::Sphere(Point3D c, double r)
	: _center{c}
	, _radius(r)
	, _inv_area{1.0 / (4*PI<double>*r*r)}
{}


// ---------------------------------------------------------------- clone

Sphere* 
Sphere::clone(void) const {
	return (new Sphere(*this));
}


// ---------------------------------------------------------------- copy constructor

void Sphere::set_center(const Point3D& c) {
	_center = c;
}

void Sphere::set_center(const double x, const double y, const double z) {
	_center.x = x;
	_center.y = y;
	_center.z = z;
}

void Sphere::set_radius(const double r) {
	_radius = r;
}

// ---------------------------------------------------------------- assignment operator

Sphere& 
Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	_center 	= rhs._center;
	_radius	= rhs._radius;

	return (*this);
}

//---------------------------------------------------------------- hit

bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	Vector3D	temp 	= ray.o - _center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - _radius * _radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal 	 = (temp + t * ray.d) / _radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > kEpsilon) {
			tmin = t;
			sr.normal   = (temp + t * ray.d) / _radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return (true);
		} 
	}
	
	return (false);
}

bool Sphere::shadow_hit(Ray const & ray, double & tmin) const {
	if (!casts_shadows())
		return false;

	double 		t;
	Vector3D	temp 	= ray.o - _center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - _radius * _radius;
	double 		disc	= b * b - 4.0 * a * c;

	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root

		if (t > kEpsilon) {
			tmin = t;
			return true;
		}

		t = (-b + e) / denom;    // larger root

		if (t > kEpsilon) {
			tmin = t;
			return true;
		}
	}

	return (false);
}

void Sphere::set_sampler(std::shared_ptr<Sampler> sampler) {
	_sampler = sampler;
	_sampler->map_samples_to_sphere();
}

Point3D Sphere::sample() {
	Point3D sp = _sampler->sample_sphere();
	return _center + sp * _radius;
}

Normal Sphere::get_normal(Point3D const & p) {
	Vector3D n = p - _center;
	n.normalize();
	return n;
}

float Sphere::pdf(ShadeRec const &) const {
	return _inv_area;
}
