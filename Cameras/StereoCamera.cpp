//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

//  Copyright notice for changes since the originally published version:
//  Copyright (C) Eduárd Mándy 2019-2021
//  Though this C++ code was change in a large measure it still has the original copyright notice.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.

#include "StereoCamera.h"
#include "Utilities/RGBColor.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Utilities/Maths.h"
#include "Samplers/Sampler.h"
#include "World/ViewPlane.h"
#include "World/World.h"

using std::unique_ptr, std::move;

ViewingType	viewing_type;		// parallel or transverse viewing
int			pixel_gap;			// gap in pixels between the left and right images
float		beta;				// stereo separation angle
Camera *left_camera_ptr;	// left eye camera
Camera *right_camera_ptr;	// right eye camera

StereoCamera::StereoCamera(void)
	:	Camera(),
		viewing_type(ViewingType::parallel),
		pixel_gap(5),
		beta(5.0f),
		left_camera_ptr(nullptr),
		right_camera_ptr(nullptr)
{}

StereoCamera::StereoCamera(unique_ptr<Camera> left_camera, unique_ptr<Camera> right_camera)
	:	viewing_type(ViewingType::parallel),
		pixel_gap(5),
		beta(5.0f),
		left_camera_ptr(move(left_camera)),
		right_camera_ptr(move(right_camera))
{}

StereoCamera::StereoCamera(const StereoCamera& c)
	: 	Camera{c},
	viewing_type(c.viewing_type),
	pixel_gap(c.pixel_gap),
	beta(c.beta)
{
	if (c.left_camera_ptr)
		left_camera_ptr.reset(c.left_camera_ptr->clone());

	if (c.right_camera_ptr)
		right_camera_ptr.reset(c.right_camera_ptr->clone());
}

Camera*
StereoCamera::clone(void) const {
	return (new StereoCamera(*this));
}

StereoCamera&
StereoCamera::operator= (const StereoCamera& rhs) {
	if (this == &rhs)
		return *this;

	Camera::operator=(rhs);

	viewing_type = rhs.viewing_type;
	pixel_gap = rhs.pixel_gap;
	beta = rhs.beta;
	
	if (rhs.left_camera_ptr)
		left_camera_ptr.reset(rhs.left_camera_ptr->clone());

	if (rhs.right_camera_ptr)
		right_camera_ptr.reset(rhs.right_camera_ptr->clone());

	return *this;
}

void
StereoCamera::setup_cameras(void) {
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * radians(beta));  //  half the camera separation distance

	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();

	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();
}

void StereoCamera::render_scene(World const & w, float x, int offset) {
	ViewPlane	vp 		= w.vp;
	int 		hres	= vp.hres;
	int 		vres 	= vp.vres;

	double r = eye.distance(lookat);
	float x2 = static_cast<float>(r * tan(0.5 * radians(beta)));

	if (viewing_type == parallel) {
		left_camera_ptr->render_scene(w, x2, 0);						// left view on left
		right_camera_ptr->render_scene(w, -x2, hres + pixel_gap);   	// right view on right
	}

	if (viewing_type == transverse) {
		right_camera_ptr->render_scene(w, -x2, 0);   					// right view on left
		left_camera_ptr->render_scene(w, x2, hres + pixel_gap);    		// left view on right
	}
}
