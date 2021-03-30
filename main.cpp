#include <chrono>
#include <Magick++.h>
#include "World/World.h"
#include "UserInterface/Terminal.h"

using std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::milliseconds;
using namespace Magick;

int main(int argc, char * argv[])
{
	World w;
	w.build();

	Image im{Geometry{w.vp.hres, w.vp.vres}, ColorRGB{0, 0, 0}};
	RenderThread t{w, im};

	auto t0 = steady_clock::now();

	w.render_scene();

	auto dt = steady_clock::now() - t0;
	cout << "render takes: " << duration_cast<milliseconds>(dt).count() << "ms\n";

	im.write("out.png");
	return 0;
}
