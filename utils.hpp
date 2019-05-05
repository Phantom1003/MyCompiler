#ifndef UTILS
#define UTILS

#include <string>
#include <sstream>

int s2i(std::string s) {
	return std::stoi(s);
}

double s2d(std::string s) {
	return std::stod(s);
}

std::string i2s(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

std::string d2s(double d) {
	std::stringstream ss;
	ss << d;
	return ss.str();
}

#endif