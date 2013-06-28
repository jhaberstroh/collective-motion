#include "tissuecell.h"
#include "MersenneTwister.h"
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <assert.h>

void RandomVectorTest(){
	TissueCell::Vector myvector(100);

	MTRand rng;
	std::generate(myvector.begin(), myvector.end(), [&rng]() -> TissueCell::Unit 
								{return TissueCell::Unit::CreateRandom(rng);} );

	for (auto& cell : myvector){
		assert(cell.x <= 1 && cell.x >= 0);
		assert(cell.y <= 1 && cell.y >= 0);
		assert(cell.angle <= 1 && cell.angle >= 0);
	}

	assert(myvector.size() == 100);
}


void WalkerPairTest(){
	TissueCell::Vector cells(2);

	MTRand rng;

	std::generate(cells.begin(), cells.end(), [&rng]() -> TissueCell::Unit 
								{return TissueCell::Unit::CreateRandom(rng);} );

	TissueCell::Interact(cells[0], cells[1], 1., 5./6., 10, .75, 30);

	for (auto& cell : cells){
		cell.TakeStep(.01, 1, 1, 1, .001, 10., rng);
	}

}




int main(){
	RandomVectorTest();
}
