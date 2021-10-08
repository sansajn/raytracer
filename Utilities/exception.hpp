#pragma once
#include <exception>
#include <string>
#include <string_view>

/*! Exception with stacktrace dump.
\code
throw default_implementation{__PRETTY_FUNCTION__};
\endcode */
class default_implementation : public std::exception {
public:
	default_implementation(std::string_view where);
	char const * what() const noexcept override;

private:
	std::string _what;
};
