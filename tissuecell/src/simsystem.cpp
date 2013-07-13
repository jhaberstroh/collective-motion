#include <iostream>
#include "simsystem.h"

void TissueCell::SimSystem::PrintParams(){
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

void TissueCell::SimSystem::LinearZoom(double zoom_factor){
	
	v0 *= zoom_factor;
	mob *= zoom_factor;
	box_size *= zoom_factor;
	Req *= zoom_factor;
	Rcut *= zoom_factor;
}

void TissueCell::SimSystem::GenerateCubicLattice(uint n_length){
	RealType sep = box_size / n_length;
	for (uint i = 0 ; i < n_length ; i++){
		for (uint j = 0 ; j < n_length ; j++){
			system.push_back(CellData::Create_xy(i*sep, j*sep));
		}
	}
}

void TissueCell::SimSystem::TimeStep(){
	m_total_time += dt;
	// Sum only the upper-half box to avoid interaction repetition
	// Also skip the diagonal, self-interaction
	for (uint i = 0 ; i < system.size() ; ++i){
		for (uint j = i + 1 ; j < system.size() ; ++j){
			Interact(system[i], system[j], Rcut, Req, box_size, Fadh, Frep);
		}
	}
	for (auto& cell : system){
		cell.TakeStep(dt, v0, mob, t_relax, noise, box_size, rng);
	}
}
