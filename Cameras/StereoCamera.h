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

typedef enum {
	parallel,
	transverse
} ViewingType;

#include <memory>
#include "Cameras/Camera.h"
#include "Utilities/Point2D.h"

class StereoCamera: public Camera {
	public:

		StereoCamera();

		StereoCamera(std::unique_ptr<Camera> left_camera, std::unique_ptr<Camera> right_camera);

		StereoCamera(const StereoCamera& ph);

		virtual Camera*
		clone(void) const override;

		StereoCamera&
		operator= (const StereoCamera& rhs);

		void
		setup_cameras(void);

		void render_scene(World const & w, float x = 0, int offset = 0) override;

		void
		use_parallel_viewing();

		void
		use_transverse_viewing();

		void
		set_pixel_gap(int gap);

		void
		set_stereo_angle(float angle);

	private:

		ViewingType	viewing_type;		// parallel or transverse viewing
		int			pixel_gap;			// gap in pixels between the left and right images
		float		beta;				// stereo separation angle
		std::unique_ptr<Camera> left_camera_ptr,	 // left eye camera
			right_camera_ptr;	 // right eye camera
};

inline void
StereoCamera::use_parallel_viewing() {
	viewing_type = ViewingType::parallel;
}

inline void
StereoCamera::use_transverse_viewing() {
	viewing_type = ViewingType::transverse;
}

inline void
StereoCamera::set_pixel_gap(int gap) {
	pixel_gap = gap;
}

inline void
StereoCamera::set_stereo_angle(float angle) {
	beta = angle;
}
