#ifndef __CAMERA__
#define __CAMERA__

// This file contains the declaration of the base class Camera
// There is no view plane distance because the fisheye and panoramic cameras don't use it

#include "Point3D.h"
#include "Vector3D.h"

class World;  // can't #include "World" here because World contains a camera pointer

//--------------------------------------------------------------------- class Camera

class Camera {
	public:
		Camera();
		virtual void render_scene(const World& w) = 0;
		void set_eye(const Point3D& p);
		void set_lookat(const Point3D& p);
		void set_up_vector(const Vector3D& u);
		void set_roll(const float ra);
		void set_exposure_time(const float exposure);
		void compute_uvw();

		Camera(const Camera& camera);
		virtual Camera * clone() const = 0;
		virtual ~Camera() = default;
		
	protected:		
		Point3D eye;				// eye point
		Point3D lookat; 			// lookat point
		float ra;					// roll angle
		Vector3D	u, v, w;			// orthonormal basis vectors
		Vector3D	up;					// up vector
		float	exposure_time;
		
		Camera& 							// assignment operator
		operator= (const Camera& camera);
};


// inlined access functions


// ----------------------------------------------------------------- set_eye

inline void
Camera::set_eye(const Point3D& p) {
	eye = p;
}

// ----------------------------------------------------------------- set_lookat

inline void
Camera::set_lookat(const Point3D& p) {
	lookat = p;
}

// ----------------------------------------------------------------- set_up_vector

inline void
Camera::set_up_vector(const Vector3D& u) {
	up = u;
}

// ----------------------------------------------------------------- set_roll

inline void
Camera::set_roll(const float r) { 
	ra = r;
}


// ----------------------------------------------------------------- set_exposure_time

inline void
Camera::set_exposure_time(const float exposure) {
	exposure_time = exposure;
}


#endif
