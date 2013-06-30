#include <cxxtest/TestSuite.h>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "analyze.h"
#include "MersenneTwister.h"

class AnalyzeTest : public CxxTest::TestSuite {
public:
	void testEmpty(void){
		std::vector<double> angles;
		double vbar = analyze::OPVbar(angles);
		TS_ASSERT( isnan(vbar) );
	}

	void testLargeRand(void){
		double pi = 3.14159265359;

		std::vector<double> angles(1000000); //1 Million
		MTRand rng;
		for (auto& ang : angles){
			ang = rng.rand(2 * pi);
		}
		
		double vbar = analyze::OPVbar(angles);
		TS_ASSERT_DELTA(vbar, 0, .01);
	}


	void testOne(void){
		double pi = 3.14159265359;

		std::vector<double> angles(1000000); //1 Million
		MTRand rng;
		for (auto& ang : angles){
			ang = 0.2;
		}
		
		double vbar = analyze::OPVbar(angles);
		TS_ASSERT_DELTA(vbar, 1, .000001);
	}

};
