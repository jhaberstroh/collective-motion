#include "tissuesimulation.h"

int main(int argc, char ** argv){
	TissueSimulation sim(true);
	
	sim.GenerateSquareLattice(3);
	sim.TimeStep();
}
