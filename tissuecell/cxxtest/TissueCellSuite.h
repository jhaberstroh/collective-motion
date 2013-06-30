#include <cxxtest/TestSuite.h>
#include <cmath>
#include "tissuecell.h"
#include "MersenneTwister.h"

class TissueCellSuite : public CxxTest::TestSuite {
private:
		MTRand rng;
		TissueCell::RealType pi;
		TissueCell::RealType err;
		// Floating point error constrained below 6 decimial points
		TissueCell::Unit u1, u2;


public:
	void setUp(){
		rng = MTRand(90210);
		pi = 3.14159265359;
		err = .000001;
		// Floating point error constrained below 6 decimial points
	}

	void testCreate(void){
		u1 = TissueCell::Unit::Create_xya(3,4,3.1);
		TS_ASSERT_EQUALS(u1.x, 3);
	}

	void testCardinalUnit(void){
		TissueCell::RealType dx, dy, angle;

		angle = 0;
		dx = 1;
		dy = 0;
		u1 = TissueCell::Unit::Create_xya(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi/2;
		dx = 0;
		dy = 1;
		u1 = TissueCell::Unit::Create_xya(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = pi;
		dx =-1;
		dy = 0;
		u1 = TissueCell::Unit::Create_xya(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);

		angle = 3 * pi / 2;
		dx = 0;
		dy =-1;
		u1 = TissueCell::Unit::Create_xya(4,4,angle);
		u1.TakeStep(1, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_EQUALS(u1.x, 4 + dx);
		TS_ASSERT_EQUALS(u1.y, 4 + dy);
	}
	
	void testLRUDMoveReal(void){
		TissueCell::Unit u1 = TissueCell::Unit::Create_xya(4.1,4.1,0);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 5.3,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 5.3,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,2*pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 2.9,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,3*pi/2);
		u1.TakeStep(1.2, 1, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 2.9,err);
	}

	void testLRUDForceReal(void){
		MTRand rng;
		TissueCell::RealType pi = 3.14159265359;
		TissueCell::RealType err = .000001;
		// Floating point error constrained below 6 decimial points

		TissueCell::Unit u1 = TissueCell::Unit::Create_xya(4.1,4.1,0);
		u1.Fx = 1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 5.3,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,pi/2);
		u1.Fy = 1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 5.3,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,2*pi/2);
		u1.Fx = -1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 2.9,err);
		TS_ASSERT_DELTA(u1.y, 4.1,err);
		
		u1 = TissueCell::Unit::Create_xya(4.1,4.1,3*pi/2);
		u1.Fy = -1.2;
		u1.TakeStep(1, 0, 1, 1, 0, 10, rng);
		TS_ASSERT_DELTA(u1.x, 4.1,err);
		TS_ASSERT_DELTA(u1.y, 2.9,err);
	}


	void testOneInteract(void){
		u1 = TissueCell::Unit::Create_xya(3.5, 3.5, 0);
		u2 = TissueCell::Unit::Create_xya(4.5, 3.5, pi);

		TissueCell::Interact(u1, u2, 4, 2, 10, 0, .8); //Repulsive force of .8 to push particles spaced at 1 by .4

		u1.TakeStep(1, 0, 1, 1, 0, 10, rng); //dt = 1, v = 0, noise=0
		u2.TakeStep(1, 0, 1, 1, 0, 10, rng);

		TS_ASSERT_DELTA(u1.x, 3.1, err);
		TS_ASSERT_DELTA(u1.y, 3.5, err);
		TS_ASSERT_DELTA(u2.x, 4.9, err);
		TS_ASSERT_DELTA(u2.y, 3.5, err);
	}


};
