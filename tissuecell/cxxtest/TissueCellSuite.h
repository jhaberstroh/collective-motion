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
		TissueSimulation sim;

public:
	void setUp(){
		pi = 3.14159265359;
		err = .000001;
		// Floating point error constrained below 6 decimial points
		seed = rng.rand(10000000);
		rng.seed(seed);
		sim.SetFadh(.75);
		sim.SetFrep(10);
		sim.set_seed(seed);
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
		u1 = TissueCell(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi/2;
		dx = 0;
		dy = 1;
		u1 = TissueCell(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi;
		dx =-1;
		dy = 0;
		u1 = TissueCell(4,4,angle);
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
		sim.Reset(true);
		sim.GenerateSquareLattice(1);
		//std::vector<TissueCell> dat(sim.ViewRaw());
		//for (auto cell : dat){
		//	cell.print();
		//}
		sim.TimeStep();
	}
	
	void testLRUDMoveReal(void){
		TissueCell u1 = TissueCell(4.1,4.1,0);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 5.3,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell(4.1,4.1,pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 5.3,err);
		
		u1 = TissueCell(4.1,4.1,2*pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 2.9,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell(4.1,4.1,3*pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 2.9,err);
	}

	void testLRUDForceReal(void){
		MTRand rng(seed);
		TissueCell::RealType pi = 3.14159265359;
		TissueCell::RealType err = .000001;
		// Floating point error constrained below 6 decimial points

		TissueCell u1 = TissueCell(4.1,4.1,0);
		u1.Fx = 1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 5.3,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell(4.1,4.1,pi/2);
		u1.Fy = 1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 5.3,err);
		
		u1 = TissueCell(4.1,4.1,2*pi/2);
		u1.Fx = -1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 2.9,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell(4.1,4.1,3*pi/2);
		u1.Fy = -1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 2.9,err);
	}

	void testOneInteract(void){
		TissueCell u1(3.5, 3.5, 0);
		TissueCell u2(4.5, 3.5, pi);

		u1.Interact(u2, 4, 2, 10, 0, .8); //Repulsive force of .8 to push particles spaced at 1 by .4

		u1.TakeStep(1, 0, 1, 1, 0, 10, rng); //dt = 1, v = 0, noise=0
		u2.TakeStep(1, 0, 1, 1, 0, 10, rng);

		TS_ASSERT_DELTA(u1.x, 3.1, err);
		TS_ASSERT_DELTA(u1.y, 3.5, err);
		TS_ASSERT_DELTA(u2.x, 4.9, err);
		TS_ASSERT_DELTA(u2.y, 3.5, err);
	}

	void testManyBalance(void){
		TissueCell u1(3.5, 3.5, 0);
		TissueCell u2(4.5, 3.5, pi);

		for (int i = 0 ; i < 10000 ; i++){
			u1.Interact(u2, 4, 2, 10, 0, .8); //Repulsive force of .8 to push particles spaced at 1 by .4
	
			u1.TakeStep(1, .4, 1, 100000000000, 0, 10, rng); //dt = 1, v = .4, noise=0
			u2.TakeStep(1, .4, 1, 100000000000, 0, 10, rng);
		}

		TS_ASSERT_DELTA(u1.x, 3.5, err);
		TS_ASSERT_DELTA(u1.y, 3.5, err);
		TS_ASSERT_DELTA(u2.x, 4.5, err);
		TS_ASSERT_DELTA(u2.y, 3.5, err);
	}


	void testGenerateLattice(void){
		sim.Reset(true);
		sim.GenerateSquareLattice(1);

		const std::vector<TissueCell>& data = sim.ViewRaw();
		for (uint i = 0 ; i < data.size() ; i++){
			TS_ASSERT_DELTA(data[i].x, 0, err);
			TS_ASSERT_DELTA(data[i].y, 0, err);
		}
	}

	void testTwoStepNoForce(void){
		sim.Reset(true);
		sim.SetFadh(0);
		sim.SetFrep(0);

		sim.GenerateSquareLattice(3);
		
		std::vector<TissueCell> data_start(sim.ViewRaw());

		for (int i = 0 ; i < 2 ; i++){
			sim.TimeStep();
		}
			
		std::vector<TissueCell> data_end(sim.ViewRaw());
	
		for (uint i = 0 ; i < data_start.size() ; i++){
			if (data_start[i].x == data_end[i].x && data_start[i].y == data_end[i].y){
				TS_FAIL("One of the particles did not move");
			}
		}
	}
};
