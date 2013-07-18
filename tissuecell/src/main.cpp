#include "tissuecell.h"
#include "MersenneTwister.h"
#include <algorithm>
#include <vector>


int main(int argc, char ** argv){
	TissueSimulation sim;
	
	sim.GenerateSquareLattice(3);
	sim.TimeStep();
}
