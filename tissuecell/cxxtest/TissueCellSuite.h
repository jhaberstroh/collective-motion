#include <cxxtest/TestSuite.h>
#include <cmath>
#include "tissuesimulation.h"
#include "MersenneTwister.h"

class TissueCellSuite : public CxxTest::TestSuite {
	typedef uint uint32;
private:
		MTRand rng;
		TissueCell::RealType pi;
		TissueCell::RealType err;
		// Floating point error constrained below 6 decimial points
		int seed;

public:
	void setUp(){
		pi = 3.14159265359;
		err = .000001;
		// Floating point error constrained below 6 decimial points
		seed = rng.rand(10000000);
		std::cout << "SEED: " << seed << std::endl;
	}

	void testOneStep(void){
		TissueSimulation sim;

		sim.GenerateSquareLattice(1);
		sim.TimeStep();
	}

};
