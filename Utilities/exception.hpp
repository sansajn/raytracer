#pragma once
#include <exception>
#include <string>
#include <string_view>

class default_implementation : public std::exception {
public:
	default_implementation(std::string_view where);
	char const * what() const noexcept override;

private:
	std::string _what;
};
