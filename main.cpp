#include <chrono>
#include <vector>
#include <iostream>
#include <Magick++.h>
#include "World/World.h"
#include "UserInterface/Terminal.h"

using std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::milliseconds;
using std::vector;
using std::cout;
using namespace Magick;

int main(int argc, char * argv[])
{
	World w;
	w.build();

#ifdef RENDER_PARALLEL
	vector<RGBColor> pixels(w.vp.hres * w.vp.vres);
	RenderThread t{w, pixels};
#else
	Image im{Geometry{w.vp.hres, w.vp.vres}, ColorRGB{0, 0, 0}};
	RenderThread t{w, im};
#endif

	auto t0 = steady_clock::now();

	w.render_scene();

	auto dt = steady_clock::now() - t0;
	cout << "render takes: " << duration_cast<milliseconds>(dt).count() << "ms\n";

#ifdef RENDER_PARALLEL
	// TODO: save image data

	// convert RGBColor to bytes
	vector<uint8_t> bytes(size(pixels) * 3);
	for (size_t i = 0; i < size(pixels); ++i)
	{
		RGBColor const & rgb = pixels[i];
		uint8_t * p = &bytes[i*3];
		*p++ = uint8_t(rgb.r * 255);
		*p++ = uint8_t(rgb.g * 255);
		*p = uint8_t(rgb.b * 255);
	}

	Image im;
	im.read(w.vp.hres, w.vp.vres, "RGB", StorageType::CharPixel, bytes.data());
	im.write("out.png");
#else
	im.write("out.png");
#endif

	return 0;
}
