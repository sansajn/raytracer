#pragma once
#include <utility>
#include <cstddef>

class PixelRange {
public:
	PixelRange(size_t w, size_t h)
		: _w{w}, _h{h}
	{}

	void operator++() {
		++_c;
		if (_c > _w) {  // columns are iterated with `c <= hres` condition (see `World.cpp:render_scene()`)
			_c = 0;

			++_r;
			if (_r >= _h)
				_r = _h;  // end of range
		}
	}

	std::pair<size_t, size_t> operator*() const {
		return {_c, _r};
	}

	PixelRange begin() {return *this;}
	PixelRange end() {return PixelRange{0, 0};}

	// comparison for for-each loop
	bool operator==(PixelRange const & rhs) const {
		return _h == _r && rhs._w == 0 && rhs._h == 0;
	}

	bool operator!=(PixelRange const & rhs) const {
		return !(*this == rhs);
	}

private:
	size_t _w, _h, _c = 0, _r = 0;
};
