#ifndef __TISSUECELL_H_DEFINED__
#define __TISSUECELL_H_DEFINED__

// tissuecell.h
//================================================
// Defines the TissueCell namespace.
// In this namespace, we define typedefs for a single cell (Unit) and a vector of cells (Collection).
#ifdef DP
#define MACRO_PRECISION double
#else
#define MACRO_PRECISION float
#endif

#include <iostream>
#include <vector>
#include "MersenneTwister.h"
#include "dependency.h"


namespace TissueCell{

	// Create the data struct with either a float or a double to vary precision
	template <class sp_or_dp>
		struct CellData
	{
		typedef sp_or_dp real_type;
		real_type angle;
		real_type x;
		real_type y;
		real_type Fx;
		real_type Fy;
	
		CellData(real_type mx, real_type my, real_type ma): x(mx), y(my), angle(ma) {};
		CellData(): x(0), y(0), angle(0) {};

		static CellData<real_type> Create_xya(real_type mx, real_type my, real_type ma){
			return CellData(mx,my,ma);}

		static CellData<real_type> CreateRandom(MTRand& rng){
			return CellData(rng.rand(), rng.rand(), rng.rand());}

		void TakeStep(real_type dt, real_type v0, real_type mob, real_type t_relax, real_type noise, real_type box_size, MTRand& rng);
	};

	typedef MACRO_PRECISION RealType;
	typedef CellData<MACRO_PRECISION> Unit;
	typedef std::vector<Unit> Vector;

	/// Create a mutual interaction, where each cell moves relative to the other. Because forces are additive
	///  Interaction range is (-box_size/2, box_size/2] (open on bottom, closed on top).
	///  All particles must begin inside of the box.
	///  Throws an invalid_argument exception if Rcut <= Req
	void Interact(Unit& cell1, Unit& cell2, RealType r_cut, RealType r_eq, RealType box_size, RealType F_adh, RealType F_rep);


}


#endif 
