#include <chrono>
#include <vector>
#include <filesystem>
#include <iostream>
#include <cassert>
#include <Magick++.h>
#include "World/World.h"
#include "UserInterface/Terminal.h"

using std::chrono::steady_clock, std::chrono::duration_cast, std::chrono::milliseconds;
using std::vector;
using std::cout;
using std::filesystem::path;
using namespace Magick;

void save_image(vector<RGBColor> const & pixels, size_t w, size_t h, path const & fname)
{
	assert(w*h == size(pixels));

	// first, convert RGBColor to bytes
	vector<uint8_t> bytes(size(pixels) * 3);

	for (size_t r = 0; r < h; ++r)
	{
		for (size_t c = 0; c < w; ++c)
		{
			RGBColor const & rgb = pixels[c + (r*w)];
			size_t x = c;
			size_t y = h - r - 1;
			size_t idx = x + (w*y);
			uint8_t * p = &bytes[idx*3];
			*p++ = uint8_t(rgb.r * 255);
			*p++ = uint8_t(rgb.g * 255);
			*p = uint8_t(rgb.b * 255);
		}
	}

	Image im;
	im.read(w, h, "RGB", StorageType::CharPixel, bytes.data());
	im.write(fname.string());
}

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
	save_image(pixels, w.vp.hres, w.vp.vres, "out.png");
#else
	im.write("out.png");
#endif

	return 0;
}
