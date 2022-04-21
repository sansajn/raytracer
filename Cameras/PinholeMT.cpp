#include <algorithm>
#include <execution>
#include "Utilities/pixel_pos_view.hpp"
#include "PinholeMT.h"

#include <thread>
#include <mutex>
#include <unordered_set>
#include <iostream>
using std::cout, std::unordered_set, std::lock_guard, std::mutex;

using std::pair, std::transform;

void PinholeMT::render_scene(const World& w) {
	RGBColor	L;
	ViewPlane vp{w.vp};
	int const n = (int)sqrt((float)vp.num_samples);

	vp.s /= zoom();

	// debugging
	unordered_set<std::thread::id> tids(16);
	mutex tids_locker;

	auto pixel_rng = pixel_pos_view(vp.hres, vp.vres);
	transform(std::execution::par, begin(pixel_rng), end(pixel_rng), begin(w.pixels),  // parallel transform
		[&tids, &tids_locker, &vp, &w, n, this](pair<size_t, size_t> pixel_pos){
			{
				lock_guard lock{tids_locker};
				tids.insert(std::this_thread::get_id());
			}

			RGBColor L{black};
			Ray ray;
			ray.o = eye;

			auto & [c, r] = pixel_pos;
			for (int p = 0; p < n; ++p) {  // up pixel
				for (int q = 0; q < n; ++q) {  // across pixel
					Point2D sp = vp.sampler_ptr->sample_unit_square();
					Point2D pp;  // sample point on a pixel
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
					ray.d = get_direction(pp);
					L += w.tracer_ptr->trace_ray(ray, 0);
				}
			}

			L /= vp.num_samples;
			L *= exposure_time;

			return w.map_to_pixel_color(L);
		});

	cout << "used-threads=" << size(tids) << "\n";
}
