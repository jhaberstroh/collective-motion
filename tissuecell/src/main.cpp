#include "tissuecell.h"
#include "tissuecellgui.h"
#include "MersenneTwister.h"
#include <algorithm>
#include <vector>


int main(int argc, char ** argv){
	TissueCell::Vector myvector(100);

	MTRand rng;
	std::generate(myvector.begin(), myvector.end(), [&rng]() -> TissueCell::Unit 
								{return TissueCell::Unit::CreateRandom(rng);} );

	for (auto& cell : myvector){
		std::cout << "Random x position: " << cell.x << std::endl;
	}

	RenderFrame1Sec(argc, argv, std::vector<TissueCell::RealType>());
}
