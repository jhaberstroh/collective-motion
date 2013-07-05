#include "simsystem.h"
#include <iostream>

TissueCell::SimSystem::PrintParams(){
			std::cout << "dt = " << dt << std::endl;
			std::cout << "v0 = " << v0 << std::endl;
			std::cout << "mob = " << mob << std::endl;
			std::cout << "t_relax = " << t_relax << std::endl;
			std::cout << "noise = " << noise << std::endl;
			std::cout << "box_size = " << box_size << std::endl;
			std::cout << "Fadh = " << Fadh << std::endl;
			std::cout << "Frep = " << Frep << std::endl;
			std::cout << "Req = " << Req << std::endl;
			std::cout << "Rcut = " << Rcut << std::endl;
}
