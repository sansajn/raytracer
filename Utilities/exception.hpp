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

/*! Exception with stacktrace dump for calling not implemented code.
\code
throw not_implemented{__PRETTY_FUNCTION__};
\endcode */
class not_implemented : public std::exception {
public:
	not_implemented(std::string_view where);
	char const * what() const noexcept override;

private:
	std::string _what;
};
