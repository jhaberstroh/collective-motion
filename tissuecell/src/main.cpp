#include "tissuesimulation.h"

int main(int argc, char ** argv){
	TissueSimulation sim;
	
	sim.GenerateSquareLattice(3);
	sim.TimeStep();
}
