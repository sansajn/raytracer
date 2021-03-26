#include "terminal.h"

RenderThread::RenderThread(World & w, Magick::Image & im)
	: _w{w}
	, _im{im}
{
	w.paintArea = this;
}

void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{
	int x_max = _w.vp.hres,
		y_max = _w.vp.vres-1;

	int img_x = ((double)x / x_max) * (_im.columns() - 1),
		img_y = ((double)y / y_max) * (_im.rows() - 1);

	try {
		_im.pixelColor(img_x, img_y, Magick::ColorRGB{red/255.0, green/255.0, blue/255.0});
	}
	catch (std::exception & e) {
		cout << e.what() << " for (" << x << ", " << y << ") pixel" << std::endl;
	}
}
