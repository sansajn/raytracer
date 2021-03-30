#pragma once
#include <utility>
#include <cstddef>

class pixel_range {
public:
	pixel_range(size_t w, size_t h)
		: _w{w}, _h{h}
	{}

	void operator++() {
		++_c;
		if (_c > _w) {  // columns are iterated with `c <= hres` condition
			_c = 0;

			++_r;
			if (_r >= _h)
				_r = _h;  // end of range
		}
	}

	std::pair<size_t, size_t> operator*() const {
		return {_c, _r};
	}

	pixel_range begin() {return *this;}
	pixel_range end() {return pixel_range{0, 0};}

	// comparsion for for-each loop
	bool operator==(pixel_range const & rhs) const {
		return _h == _r && rhs._w == 0 && rhs._h == 0;
	}

	bool operator!=(pixel_range const & rhs) const {
		return !(*this == rhs);
	}

private:
	size_t _w, _h, _c = 0, _r = 0;
};
