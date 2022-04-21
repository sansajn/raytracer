#pragma once
#include <iterator>
#include <utility>
#include <cassert>

//! Random access iterator view implemenation.
struct pixel_pos_view
	: public std::iterator<std::random_access_iterator_tag, std::pair<size_t, size_t>> {

	pixel_pos_view() : pixel_pos_view{0, 0} {}

	pixel_pos_view(size_t w, size_t h)
		: _w{w}, _h{h}, _pos{0, 0}
	{}

	reference operator*() {
		return _pos;
	}

	pointer operator->() {
		return &_pos;
	}

	pixel_pos_view & operator++() {
		auto & [c, r] = _pos;
		c += 1;
		if (c >= _w) {
			c = 0;

			r += 1;
			if (r >= _h)
				r = _h;  // end of range _pos=(0, _h)
		}
		return *this;
	}

	pixel_pos_view operator++(int) {
		auto previous = *this;
		++(*this);
		return previous;
	}

	pixel_pos_view & operator--() {
		assert(_w > 0 && _h > 0);
		assert(_h != _pos.second);  // end of range iterator

		auto & [c, r] = _pos;
		if (c == 0 && r == 0) {
			r = _h;  // end of range _pos=(0, _h)
			return *this;
		}
		else {
			if (c == 0) {
				r -= 1;  // it is safe, r > 0 by defnition there
				c = _w-1;
			}
			else
				c -= 1;
		}
		return *this;
	}

	pixel_pos_view operator--(int) {
		auto previous = *this;
		--(*this);
		return previous;
	}

	value_type operator[](int n) {  //!< element access is not possibel, we can only return its value
		return std::pair<size_t, size_t>{n%_w, n/_w};
	}

	pixel_pos_view & operator+=(int n) {
		size_t dn = _pos.second * _w + _pos.first;
		dn = std::max(dn + n, size_t{0});  // n can be < 0
		_pos.first = dn%_w;
		_pos.second = dn/_w;
		if (_pos.second >= _h)  // end of range
			_pos = std::pair<size_t, size_t>{0, _h};
		return *this;
	}

	pixel_pos_view & operator-=(int n) {
		size_t dn = _pos.second * _w + _pos.first;
		dn = std::max(dn - n, size_t{0});
		_pos.first = dn%_w;
		_pos.second = dn/_w;
		if (_pos.second >= _h)  // end of range
			_pos = std::pair<size_t, size_t>{0, _h};
		return *this;
	}

	pixel_pos_view operator+(int n) const {
		auto result = *this;
		result += n;
		return result;
	}

	pixel_pos_view operator-(int n) const {
		auto result = *this;
		result -= n;
		return result;
	}

	difference_type operator-(pixel_pos_view const & pos) const {
		assert((_w == pos._w && _h == pos._h)
			|| end_of_range()
			|| pos.end_of_range());

		if (end_of_range() && pos.end_of_range())
			return difference_type{0};
		else if (end_of_range())
			return (pos._w * pos._h) - (pos._pos.second * pos._w + pos._pos.first);
		else if (pos.end_of_range())
			return -((_w * _h) - (_pos.second * _w + _pos.first));
		else
			return (_pos.second * _w + _pos.first) - (pos._pos.second * pos._w + pos._pos.first);
	}

	bool operator<(pixel_pos_view const & pos) const {
		assert((_w == pos._w && _h == pos._h)
			|| end_of_range()
			|| pos.end_of_range());

		if (end_of_range())
			return false;
		else if (pos.end_of_range())
			return true;
		else {
			if (_pos.second < pos._pos.second)
				return true;
			else if (_pos.second > pos._pos.second)
				return false;
			else  // _pos.second == pos._pos.second
				return _pos.first < pos._pos.second;
		}

		// TODO: Is this "branching" implementation efficient compared to (y*w+x) < (pos.y*w+pos.x)?
	}

	bool operator<=(pixel_pos_view const & pos) const {
		assert((_w == pos._w && _h == pos._h)
			|| end_of_range()
			|| pos.end_of_range());

		if (pos.end_of_range())
			return true;
		else if (end_of_range())
			return false;
		else {
			if (_pos.second < pos._pos.second)
				return true;
			else if (_pos.second > pos._pos.second)
				return false;
			else  // _pos.second == pos._pos.second
				return _pos.first <= pos._pos.second;
		}
	}

	bool operator>(pixel_pos_view const & pos) const {
		return !(*this <= pos);
	}

	bool operator>=(pixel_pos_view const & pos) const {
		return !(*this < pos);
	}

	bool operator==(pixel_pos_view const & rhs) const {
		return (_w == rhs._w && _h == rhs._h && _pos == rhs._pos)
			|| (end_of_range() && rhs.end_of_range());
	}

	bool operator!=(pixel_pos_view const & rhs) const {
		return !(*this == rhs);
	}

	pixel_pos_view begin() {return *this;}
	pixel_pos_view end() {return {};}

private:
	bool end_of_range() const {return _pos.second == _h;}

	size_t _w, _h;
	std::pair<size_t, size_t> _pos;  //!< (column, row)
};  // pixel_pos_view

pixel_pos_view operator+(int n, pixel_pos_view const & pos) {
	return pos+n;
}

pixel_pos_view operator-(int n, pixel_pos_view const & pos) {
	return pos-n;
}
