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
	zoom *= zoom_factor;
	for (auto& cell : system){
		cell.x *= zoom_factor;
		cell.y *= zoom_factor;
		// Forces are not scaled because all distance parameter scaling cancels; mobility handles the length scaling
	}
}

void TissueCell::SimSystem::RandomizeAngles(){
	for (auto& cell : system){
		cell.RandomizeAngle(rng);
	}
}

void TissueCell::SimSystem::GenerateCubicLattice(uint n_length){
	RealType sep = box_size / n_length;
	for (uint i = 0 ; i < n_length ; i++){
		for (uint j = 0 ; j < n_length ; j++){
			system.push_back(CellData::Create_xy(i*sep, j*sep));
		}
	}
}

void TissueCell::SimSystem::GenerateNRandom(uint N){
	for (uint j = 0 ; j < N ; j++){
		system.push_back(CellData::CreateRandom(rng, box_size));
	}
}

void TissueCell::SimSystem::GenerateNPile(uint N, RealType x, RealType y){
	for (uint j = 0 ; j < N ; j++){
		system.push_back(CellData::Create_xy(x,y));
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

int TissueCell::SimSystem::EqStep(){
	m_total_time += dt;
	// Sum only the upper-half box to avoid interaction repetition
	// Also skip the diagonal, self-interaction
	int equil_fail = 0;
	for (uint i = 0 ; i < system.size() ; ++i){
		for (uint j = i + 1 ; j < system.size() ; ++j){
			Interact(system[i], system[j], Rcut, Req, box_size, Fadh, Frep);
		}
	}
	for (auto& cell : system){
		int fail = cell.TakeStep(dt, v0, mob, t_relax, noise, box_size, rng, true);
		if (fail){
			equil_fail = 1;
		}
	}
	return equil_fail;
}


int TissueCell::SimSystem::Equilibrate(int n_equil){
	int total_steps = 0;
	int pass_in_a_row = 0;
	while (pass_in_a_row < n_equil){
		++total_steps;
		int fail = EqStep();

		if (fail){
			pass_in_a_row = 0;
		}
		else{
			++pass_in_a_row;
		}
	}
	return total_steps;
}
