#include "tissuecell.h"
#include "MersenneTwister.h"
#include <typeinfo>
#include <algorithm>


int main(){
	TissueCell::Vector myvector(100);

	MTRand rng;
	std::generate(myvector.begin(), myvector.end(), [&rng]() -> TissueCell::Unit 
								{return TissueCell::Unit::CreateRandom(rng);} );

	for (auto& cell : myvector){
		std::cout << "Random x position: " << cell.x << std::endl;
	}
}
