#include "analyze.h"
#include <cmath>

double analyze::OPVbar(const std::vector<double>& angles){
	if (angles.size() == 0){ return nan(""); } 
	double x, y = 0;
	for (double angle : angles){
		x += std::cos(angle);
		y += std::sin(angle);
	}
	return sqrt(x * x + y * y) / angles.size();
}
