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
	void CellData::TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng)
	{
		// Handle invalid arguments
		if (mob < 0){ throw std::invalid_argument("mob < 0"); }
		if (t_relax < 0){ throw std::invalid_argument("t_relax < 0"); }
		if (noise < 0){ throw std::invalid_argument("noise < 0"); }

		RealType dx = ((std::cos(angle) * v0) + (mob * Fx)) * dt;
		RealType dy = ((std::sin(angle) * v0) + (mob * Fy)) * dt;
	
		RealType vmag = sqrt(dx * dx + dy * dy); 

		// arcsin of a cross product of two normalized vecors will give the deflection in theta.
		RealType step_noise = rng.rand() * noise;
		angle += (dt / t_relax) * std::asin( (std::cos(angle) * dy - std::sin(angle) * dx) / vmag) + step_noise;

		this->x += dx;
		this->y += dy;

		// Map x and y [0, box_size) periodically
		// e.g. box_size = 10.0, sends 10.0 -> 0.0
		if (this->x > box_size){ this->x += RealType(int(this->x/box_size)) * box_size ; } 		
		if (this->y > box_size){ this->y += RealType(int(this->y/box_size)) * box_size; } 
		// e.g. box_size = 10.0, then -10.0 -> ceil(1) -> 0 and  -10.1 -> ceil(1.01) -> 9.99
		if (this->x < 0){ this->x = this->x + ceil(-this->x/box_size) * box_size; }  
		if (this->y < 0){ this->y = this->y + ceil(-this->y/box_size) * box_size; }

		// Assertions to match the above definitions
		// Furthermore: Do not allow a particle to step more than a box width.
		assert(this->x < box_size && this->x >= 0);
		assert(this->y < box_size && this->y >= 0);

		// Clear the old forces;
		Fx = 0;
		Fy = 0;
	}



	RealType Interact(Unit& cell1, Unit& cell2, RealType Rcut, RealType Req, RealType box_size, RealType Fadh, RealType Frep){
		if (Rcut <= Req){ throw std::invalid_argument("Rcut <= Req"); }
		if (Rcut <= 0){ throw std::invalid_argument("Rcut <= 0"); }
		if (Req <= 0){ throw std::invalid_argument("Req <= 0"); }
		if (box_size <= 0){ throw std::invalid_argument("box_size <= 0"); }
		if (Fadh < 0){ throw std::invalid_argument("Fadh < 0"); }
		if (Frep < 0){ throw std::invalid_argument("Frep < 0"); }

		RealType fx;
		RealType fy;
	
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
			Fmag = Frep * (dist - Req)/Req;
			assert(Fmag  > 0);
		}
		if (dist > Req){
			Fmag = Fadh * (dist - Req)/(Rcut - Req);
			assert(Fmag < 0);
		}


		// Normalized dist vector points from cell1 to cell 2;
		cell2.Fx += dx * Fmag;
		cell2.Fy += dy * Fmag;

		cell1.Fx -= dx * Fmag;
		cell1.Fy -= dy * Fmag;
		return Fmag;
	}
}


