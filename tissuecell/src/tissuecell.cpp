#include "tissuecell.h"
#include "MersenneTwister.h"
#include <typeinfo>
#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <cmath>
#include <vector>


namespace TissueCell{
	template <class real_type>
		void CellData<real_type>::TakeStep(real_type dt, real_type v0, real_type mob, real_type t_relax, real_type noise, real_type box_size, MTRand& rng)
	{
		// Handle invalid arguments
		if (mob < 0){ throw std::invalid_argument("mob < 0"); }
		if (t_relax < 0){ throw std::invalid_argument("t_relax < 0"); }
		if (noise < 0){ throw std::invalid_argument("noise < 0"); }

		real_type dx = ((std::cos(angle) * v0) + (mob * Fx)) * dt;
		real_type dy = ((std::sin(angle) * v0) + (mob * Fy)) * dt;
	
		real_type vmag = sqrt(dx * dx + dy * dy); 

		// arcsin of a cross product of two normalized vecors will give the deflection in theta.
		real_type step_noise = rng.rand() * noise;
		angle += (dt / t_relax) * std::asin( (std::cos(angle) * dy - std::sin(angle) * dx) / vmag) + step_noise;

		x += dx;
		y += dy;

		// Map x and y [0, box_size) periodically
		// e.g. box_size = 10.0, sends 10.0 -> 0.0
		if (x > box_size){ x = x % box_size; } 		
		if (y > box_size){ y = y % box_size; } 
		// e.g. box_size = 10.0, then -10.0 -> ceil(1) -> 0 and  -10.1 -> ceil(1.01) -> 9.99
		if (x < 0){ x = x + ceil(-x/box_size) * box_size; }  
		if (y < 0){ y = y + ceil(-y/box_size) * box_size; }

		// Assertions to match the above mappingsdefinitions
		assert(x < box_size && x >= 0);
		assert(y < box_size && y >= 0);

		// Clear the old forces;
		Fx = 0;
		Fy = 0;
	}



	void Interact(Unit& cell1, Unit& cell2, RealType Rcut, RealType Req, RealType box_size, RealType Fadh, RealType Frep){
		/*
		if (Rcut <= Req){ throw std::invalid_argument("Rcut <= Req"); }
		if (Rcut <= 0){ throw std::invalid_argument("Rcut <= 0"); }
		if (Req <= 0){ throw std::invalid_argument("Req <= 0"); }
		if (box_size <= 0){ throw std::invalid_argument("box_size <= 0"); }
		if (Fadh < 0){ throw std::invalid_argument("Fadh < 0"); }
		if (Frep < 0){ throw std::invalid_argument("Frep < 0"); }

		RealType fx;
		RealType fy;
	
		RealType dx = cell1.x - cell2.x;
		RealType dy = cell1.y - cell2.y;
		if (dx > box_size / 2.0){ dx -= box_size; }
		if (dy > box_size / 2.0){ dy -= box_size; }
		if (dx <-box_size / 2.0){ dx += box_size; }
		if (dy <-box_size / 2.0){ dy += box_size; }
		
		assert(dx <= box_size / 2.0 && dx > -box_size / 2.0)
		assert(dy <= box_size / 2.0 && dy > -box_size / 2.0)

		RealType dist = sqrt(dx * dx + dy * dy);
		RealType mag;

		if (dist > Rcut){
			mag = 0;
		}
		if (dist < Req){
			mag = (dist - Req)/Req;
			assert(mag  > 0)
		}
		if (dist > Req){
			mag = (dist - Req)/(Rcut - Req);
			assert(mag < 0) 
		}
		RealType mag = 
		*/
		cell1.Fx = 1;
		cell1.Fy = 1;
		cell2.Fx = -1;
		cell2.Fy = -1;
	}
}


