#include "GeometricObjects/Compound.h"

class SolidCylinder: public Compound {
public:
	SolidCylinder();
	SolidCylinder(const double bottom, const double top, const double radius);
	SolidCylinder(const SolidCylinder& cc);
};

