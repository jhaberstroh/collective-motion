#include "tissuecell.h"
#include "MersenneTwister.h"
#include <iostream>
#include <typeinfo>


void PrintPrecision(){
	MTRand x;
	TissueCell::Unit u1 = TissueCell::Unit::CreateRandom(x);
	std::cout << typeid(u1.x).name() << std::endl;
}

int main(){
	PrintPrecision();
}
