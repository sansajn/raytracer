#pragma once
#include <iterator>
#include <utility>
#include <cstddef>

class PixelRange
	: public std::iterator<std::forward_iterator_tag, std::pair<size_t, size_t>> {

public:
	PixelRange(size_t w, size_t h)
		: _w{w}, _h{h}
	{}

	void operator++() {
		auto & [c, r] = _pos;
		++c;
		if (c >= _w) {  // note: there is a bug in World::render_scene() when computing row columns with a `c <= hres` condition, later whole additional column is not stored in bitmap
			c = 0;

			++r;
			if (r >= _h)
				r = _h;  // end of range
		}
	}

	std::pair<size_t, size_t> & operator*() {
		return _pos;
	}

	PixelRange begin() {return *this;}
	PixelRange end() {return PixelRange{0, 0};}

	// comparison for for-each loop
	bool operator==(PixelRange const & rhs) const {
		return _h == _pos.second && rhs._w == 0 && rhs._h == 0;
	}

	bool operator!=(PixelRange const & rhs) const {
		return !(*this == rhs);
	}

private:
	size_t _w, _h;
	std::pair<size_t, size_t> _pos{0, 0};  // (collumn, row)
};
