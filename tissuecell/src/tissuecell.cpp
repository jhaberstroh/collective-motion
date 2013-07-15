#include "tissuecell.h"
#include "MersenneTwister.h"
#include <typeinfo>
#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <functional>


namespace TissueCell{
	int CellData::TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng, bool eq)
	{
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
		RealType dy = ((std::sin(this->angle) * v0) + (mob * Fy)) * dt;
	
		RealType vmag = sqrt(dx * dx + dy * dy); 

		// arcsin of a cross product of two normalized vecors will give the deflection in theta.
		RealType step_noise = rng.rand() * noise;
		if (vmag != 0){
			this->angle += (dt / t_relax) * std::asin( (std::cos(angle) * dy - std::sin(angle) * dx) / vmag);
		}
		this->angle += step_noise;
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
    this->angle = fmod(fmod(this->angle, twoPi) + twoPi, twoPi);
		// Assertions to match the above definitions
		// Furthermore: Do not allow a particle to step more than a box width.
		//  (angle can rotate artibrarily)
		assert(this->x < box_size);
		assert(this->x >= 0);
		assert(this->y < box_size);
		assert(this->y >= 0);
		assert(this-> angle < twoPi);
		assert(this->angle >= 0);

		// Clear the old forces;
		this->Fx = 0;
		this->Fy = 0;
		
		return rtn;
	}



	RealType Interact(Unit& cell1, Unit& cell2, RealType Rcut, RealType Req, RealType box_size, RealType Fadh, RealType Frep){
		if (Rcut <= Req){ throw std::invalid_argument("Rcut <= Req"); }
		if (Rcut <= 0){ throw std::invalid_argument("Rcut <= 0"); }
		if (Req <= 0){ throw std::invalid_argument("Req <= 0"); }
		if (box_size <= 0){ throw std::invalid_argument("box_size <= 0"); }
		if (Fadh < 0){ throw std::invalid_argument("Fadh < 0"); }
		if (Frep < 0){ throw std::invalid_argument("Frep < 0"); }

	
		// Vector points from cell1 to cell2
		RealType dx = cell2.x - cell1.x;
		RealType dy = cell2.y - cell1.y;
		if (dx > box_size / 2.0){ dx -= box_size; }
		if (dy > box_size / 2.0){ dy -= box_size; }
		if (dx <-box_size / 2.0){ dx += box_size; }
		if (dy <-box_size / 2.0){ dy += box_size; }
		
		assert(dx <= box_size / 2.0 && dx > -box_size / 2.0);
		assert(dy <= box_size / 2.0 && dy > -box_size / 2.0);

		RealType Fmag;
		RealType dist = sqrt(dx*dx + dy*dy);
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
		cell2.Fx += dx * Fmag;
		cell2.Fy += dy * Fmag;

		cell1.Fx -= dx * Fmag;
		cell1.Fy -= dy * Fmag;
		return Fmag;
	}

	void CellData::print(){
		std::cout << "Pos, angle: (" << x <<", "<< y <<"), "<< angle << std::endl;
		std::cout << "Force: (" << Fx <<", "<< Fy <<")"<<std::endl;

	}
}


