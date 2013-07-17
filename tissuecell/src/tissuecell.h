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


namespace TissueCell{
	// Create the data struct with either a float or a double to vary precision
	typedef MACRO_PRECISION RealType;

	struct CellData
	{
		RealType angle;
		RealType x;
		RealType y;
		RealType Fx;
		RealType Fy;
	
		CellData(RealType mx, RealType my, RealType ma): angle(ma), x(mx), y(my), Fx(0), Fy(0) {};
		CellData(): angle(0), x(0), y(0), Fx(0), Fy(0) {};

		static CellData Create_xya(RealType mx, RealType my, RealType ma){
			return CellData(mx,my,ma);}

		static CellData Create_xy(RealType mx, RealType my){
			return CellData(mx,my,0);}

		static CellData CreateRandom(MTRand& rng){
			return CellData(rng.rand(), rng.rand(), rng.rand() * 2 * 3.14159265359);}
		static CellData CreateRandom(MTRand& rng, RealType box_size){
			return CellData(rng.rand() * box_size, rng.rand() * box_size, rng.rand() * 2 * 3.14159265359);}


		/// Positions are from [0, box_size), closed bottom & open top
		/// Returns non-zero to specify non-equilibrated (i.e. exploding)
		int TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng, bool eq=false);
		
		void RandomizeAngle(MTRand& rng){ angle = rng.rand() * 2 * 3.14159265359;}
		void CheckRep(RealType box_size);

		void print();
	};

	typedef CellData Unit;
	typedef std::vector<Unit> Vector;

	/// Create a mutual interaction, where each cell moves relative to the other. Because forces are additive
	///  Interaction range is (-box_size/2, box_size/2] (open on bottom, closed on top).
	///  All particles must begin inside of the box.
	///  Throws an invalid_argument exception if Rcut <= Req
	RealType Interact(Unit& cell1, Unit& cell2, RealType r_cut, RealType r_eq, RealType box_size, RealType F_adh, RealType F_rep);


}

#endif
