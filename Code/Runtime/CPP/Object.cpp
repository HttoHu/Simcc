#include "../HPP/Object.hpp"

std::string Simcc::Runtime::Basic::to_string() const
{
	switch (type)
	{
	case 0:
		return std::to_string(get_value<int>());
	case 1:
		return std::to_string(get_value<int64_t>());
	case 2:
		return std::string(1, get_value<char>());
	case 3:
		return get_value<std::string>();
	case 4:
		return std::to_string(get_value<double>());
	case 5:
		if (get_value<bool>())
			return "true";
		return "false";
	default:
		throw std::runtime_error("unkown type!");
	}
}
