#include <sstream>
#include <boost/stacktrace.hpp>
#include "exception.hpp"

using std::string_view, std::ostringstream;

default_implementation::default_implementation(string_view where) {
	ostringstream oss;

	oss << "Default implementation "
		<< "\"" << where << "\""
		<< " called, the implementation is meant to be override.\n"
		<< "\n"
		<< "Stack trace:\n"
		<< boost::stacktrace::stacktrace{} << "\n";

	_what = oss.str();
}

char const * default_implementation::what() const noexcept {
	return _what.c_str();
}
