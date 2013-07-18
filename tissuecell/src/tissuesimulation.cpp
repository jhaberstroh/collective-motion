#include "tissuesimulation.h"
#include "MersenneTwister.h"
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <functional>

void TissueSimulation::PrintParams(){
	XYASim::PrintParams();
	std::cout << "v0 = " << v0 << std::endl;
	std::cout << "mob = " << mob << std::endl;
	std::cout << "t_relax = " << t_relax << std::endl;
	std::cout << "noise = " << noise << std::endl;
	std::cout << "Fadh = " << Fadh << std::endl;
	std::cout << "Frep = " << Frep << std::endl;
	std::cout << "Req = " << Req << std::endl;
	std::cout << "Rcut = " << Rcut << std::endl;
}

void TissueSimulation::LinearZoom(RealType zoom_factor){
	XYASim::LinearZoom(zoom_factor);
	v0 *= zoom_factor;
	mob *= zoom_factor;
	Req *= zoom_factor;
	Rcut *= zoom_factor;
}


void TissueSimulation::TimeStep(){
	m_total_time += dt;
	// Sum only the upper-half box to avoid interaction repetition
	// Also skip the diagonal, self-interaction
	for (uint i = 0 ; i < m_sim_data.size() ; ++i){
		for (uint j = i + 1 ; j < m_sim_data.size() ; ++j){
			m_sim_data[i].Interact(m_sim_data[j], Rcut, Req, m_box_size, Fadh, Frep);
		}
	}
	for (auto& cell : m_sim_data){
		cell.TakeStep(dt, v0, mob, t_relax, noise, m_box_size, m_rng);
	}
}

/*
int TissueSimulation::EqStep(){
	m_total_time += dt;
	// Sum only the upper-half box to avoid interaction repetition
	// Also skip the diagonal, self-interaction
	int equil_fail = 0;
	for (uint i = 0 ; i < m_sim_data.size() ; ++i){
		for (uint j = i + 1 ; j < m_sim_data.size() ; ++j){
			Interact(m_sim_data[i], m_sim_data[j], Rcut, Req, m_box_size, Fadh, Frep);
		}
	}
	for (auto& cell : m_sim_data){
		int fail = cell.TakeStep(dt, v0, mob, t_relax, noise, m_box_size, rng, true);
		if (fail){
			equil_fail = 1;
		}
	}
	return equil_fail;
}


int TissueSimulation::Equilibrate(int n_equil){
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

*/




int TissueCell::TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng, bool eq){
		int rtn = 0;
		// Handle invalid arguments
		if (mob < 0){ throw std::invalid_argument("mob < 0"); }
		if (t_relax < 0){ throw std::invalid_argument("t_relax < 0"); }
		if (noise < 0){ throw std::invalid_argument("noise < 0"); }

		//RealType ffffx = this->Fx;
		//RealType ffffy = this->Fy;
		//RealType xxxxx = this->x;
		//RealType yyyyy = this->y;
		//RealType aaaangle = this->angle;
		

		RealType dxF = (mob * Fx) * dt;
		RealType dxV = (std::cos(this->angle) * v0) * dt;
		RealType dx = dxF + dxV;
		RealType dyF = (mob * Fy) * dt;
		RealType dyV = (std::sin(this->angle) * v0) * dt;
		RealType dy = dyF + dyV;


		RealType vmag = sqrt(dx * dx + dy * dy); 

		RealType dtheta = 0;
		// arcsin of a cross product of two normalized vecors will give the deflection in theta.
		RealType step_noise = rng.rand() * noise;
		if (vmag != 0){
			try{
				dtheta = (dt / t_relax) * std::asin( (std::cos(angle) * dy - std::sin(angle) * dx) / vmag);
				if (isnan(dtheta)){
					throw (std::cos(angle) * dy - std::sin(angle) * dx) / vmag;
				}
			}
			catch(RealType arcarg){
				std::cout << "Caught bad arctan." <<std::endl;
				if (arcarg >= 1 && arcarg <= 1.00001){
					dtheta = (dt / t_relax) * 3.141592865358979 / 2.0;
				}
				else if (arcarg <=-1 && arcarg >=-1.00001){
					dtheta = - (dt / t_relax) * 3.141592865358979 / 2.0;
				}
				else{
					throw std::domain_error("Arctangent argument outside of allowed extended domain from floating point arithmetic");
				}
			}

		}
		this->angle += step_noise;

#ifndef FORCE_WARN_OFF
		if (vmag > 10){
			std::cout << "WARNING: Assuming Req of 1: Single step is on the order of Req. Check your timestep and interaction parameters." << std::endl;
		}
#endif

		this->x += dx;
		this->y += dy;

		// Apply periodic topology:

		// Map x and y [0, box_size) periodically
		// e.g. box_size = 10.0, sends 10.0 -> 0.0
		// For a non-equilibration step:
		if (!eq){
			if (this->x >= box_size){ this->x -= box_size ;} 		
			if (this->y >= box_size){ this->y -= box_size; } 
			// e.g. box_size = 10.0, then -10.0 -> ceil(1) -> 0 and  -10.1 -> ceil(1.01) -> 9.99
			if (this->x < 0){ this->x += box_size; }  
			if (this->y < 0){ this->y += box_size; }
		}

		// For an equilibration step:
		if (eq){
			RealType beforex = this->x;
			RealType beforey = this->y;
			this->x = fmod(fmod(this->x, box_size) + box_size, box_size);
			this->y = fmod(fmod(this->y, box_size) + box_size, box_size);

			if (beforex != this->x or beforey != this->y){
				rtn = 1;
			}
		}

		RealType twoPi = 2.0 * 3.141592865358979;
		if (!(this->angle + dtheta >= 0)){
			this->angle += twoPi;
		}
		if (!(this->angle + dtheta < twoPi)){
			this->angle -= twoPi;
		}

		this->angle += dtheta;
		// Assertions to match the above definitions
		// Furthermore: Do not allow a particle to step more than a box width.
		//  (angle can rotate artibrarily)
		assert(fmod( 0 + twoPi, twoPi) == 0);
		assert(this->x < box_size);
		assert(this->x >= 0);
		assert(this->y < box_size);
		assert(this->y >= 0);
		if (!(this-> angle < twoPi)){
			std::cout << "Current angle is " << this->angle << " which is apparently larger than or equal to " << twoPi << std::endl;
			assert(this-> angle < twoPi);
		}
		if (!(this-> angle >= 0)){
			std::cout << "Current angle is " << this->angle << " which is apparently smaller than 0." << std::endl;
			assert(this->angle >= 0);
		}

		// Clear the old forces;
		this->Fx = 0;
		this->Fy = 0;
		
		return rtn;
}



TissueCell::RealType TissueCell::Interact(TissueCell& cell2, RealType Rcut, RealType Req, RealType box_size, RealType Fadh, RealType Frep){
		if (Rcut <= Req){ throw std::invalid_argument("Rcut <= Req"); }
		if (Rcut <= 0){ throw std::invalid_argument("Rcut <= 0"); }
		if (Req <= 0){ throw std::invalid_argument("Req <= 0"); }
		if (box_size <= 0){ throw std::invalid_argument("box_size <= 0"); }
		if (Fadh < 0){ throw std::invalid_argument("Fadh < 0"); }
		if (Frep < 0){ throw std::invalid_argument("Frep < 0"); }

	
		// Vector points from cell1 to cell2
		RealType dx = cell2.x - this->x;
		RealType dy = cell2.y - this->y;
		if (dx > box_size / 2.0){ dx -= box_size; }
		if (dy > box_size / 2.0){ dy -= box_size; }
		if (dx<=-box_size / 2.0){ dx += box_size; }
		if (dy<=-box_size / 2.0){ dy += box_size; }
		
		assert(dx <= box_size / 2.0);
		assert(dx > -box_size / 2.0);
		assert(dy <= box_size / 2.0);
		assert(dy > -box_size / 2.0);

		RealType Fmag = 0;
		RealType dist = sqrt(dx*dx + dy*dy);
		if (dist == 0){ 
			if (Frep != 0){
				throw std::domain_error("Interacting particles are stacked, but there is a non-zero repulsion strength. Thus, the interaction is divergent.");
			}
			return 0;
		}
		else{
			dx /= dist;
			dy /= dist;

			if (dist > Rcut){
				Fmag = 0;
				return Fmag;
			}
			if (dist < Req){
				// Flipped the convention from PRE 74, 061908
				Fmag = Frep * (Req - dist)/Req;
				assert(Fmag >= 0);
			}
			if (dist > Req){
				// Flipped the convention from PRE 74, 061908
				Fmag = Fadh * (Req - dist)/(Rcut - Req);
				assert(Fmag <= 0);
			}
	
	
			// Normalized dist vector points from cell1 to cell 2;
			
#ifndef FORCE_WARN_OFF
			if (Fmag > Req){
				if (dist > Req){
					std::cout << "WARNING: Assuming mobiliity of 1: Single attractive force is on the order of Req. Check your timestep and interaction parameters.";
				}
				if (dist < Req){
					std::cout << "WARNING: Assuming mobiliity of 1: Single repulsive force is on the order of Req. Check your timestep and interaction parameters.";
				}
			}
#endif

			cell2.Fx += dx * Fmag;
			cell2.Fy += dy * Fmag;
	
			this->Fx -= dx * Fmag;
			this->Fy -= dy * Fmag;

			

			return Fmag;
		}
}
	
void TissueCell::CheckRep(RealType box_size){
	assert(x <  box_size);
	assert(x >= box_size);
	assert(y <  box_size);
	assert(y >= box_size);
}

void TissueCell::print(){
	std::cout << "Pos, angle: (" << x <<", "<< y <<"), "<< angle << std::endl;
	std::cout << "Force: (" << Fx <<", "<< Fy <<")"<<std::endl;
}

