#include <cxxtest/TestSuite.h>
#include <cmath>
#include "tissuesimulation.h"
#include "MersenneTwister.h"

class TissueCellSuite : public CxxTest::TestSuite {
	typedef uint uint32;
	typedef TissueCell::RealType RealType;
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

	void testCreate(void){
		TissueCell u1(3,4,3.1);
		TS_ASSERT_EQUALS(u1.x, 3);
	}
	
	void testCardinalUnit(void){
		RealType dx, dy, angle;
		TissueCell u1;

		angle = 0;
		dx = 1;
		dy = 0;
		u1 = XYAData::Create_xya<TissueCell>(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi/2;
		dx = 0;
		dy = 1;
		u1 = XYAData::Create_xya<TissueCell>(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi;
		dx =-1;
		dy = 0;
		u1 = XYAData::Create_xya<TissueCell>(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = 3 * pi / 2;
		dx = 0;
		dy =-1;
		u1 = TissueCell(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);
	}


	void testOneStep(void){
		TissueSimulation sim(true);

		sim.set_seed(8143564);
		sim.GenerateSquareLattice(1);
		std::vector<TissueCell> dat(sim.ViewRaw());
		for (auto cell : dat){
			cell.print();
		}
		sim.TimeStep();
	}

};
