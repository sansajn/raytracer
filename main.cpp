#include <chrono>
#include <iostream>
#include "World/World.h"

using std::cout, std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::milliseconds;

int main(int argc, char * argv[])
{
	World w;
	w.build();

	auto t0 = steady_clock::now();

	w.camera()->render_scene(w);

	auto dt = steady_clock::now() - t0;
	cout << "render takes: " << duration_cast<milliseconds>(dt).count() << "ms\n";

	w.save_to_png();
	
	return 0;
}
