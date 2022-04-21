#include <vector>
#include <chrono>
#include <iostream>
#include <cassert>
#include "World/World.h"

using std::cout, std::endl;
using std::vector;
using std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::milliseconds;

int main(int argc, char * argv[]) {
	cout << "create scene ..." << endl;
	World w;
	w.build();

	auto t0 = steady_clock::now();

	// allocate memory for rendered data
	assert(w.vp.hres > 0 && w.vp.vres > 0);
	w.pixels.resize(w.vp.hres * w.vp.vres);

	cout << "rendering ..." << endl;
	w.camera()->render_scene(w);

	auto dt = steady_clock::now() - t0;
	cout << "render takes: " << duration_cast<milliseconds>(dt).count() << "ms\n";

	w.save_to_png();
	
	return 0;
}
