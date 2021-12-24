#pragma once
#include <string>
#include "math.h"

std::string floatToDollars(float f) {
	int cents = int(100 * f) % 100;
	std::string cents_string = std::to_string(cents);
	if (cents_string.length() == 1) {
		cents_string += "0";
	}
	int dollars = int(f);
	std::string ret = std::to_string(dollars) + "." + cents_string;
	return ret;
}