// tissuecell.h
//================================================
// Defines the TissueCell namespace.
// In this namespace, we define typedefs for a single cell (Unit) and a vector of cells (Collection).


#include <iostream>
#include <vector>
#include "MersenneTwister.h"

#ifdef DP
#define MACRO_CELLTYPE CellData<double>
#else
#define MACRO_CELLTYPE CellData<float>
#endif

namespace TissueCell{

	// Create the data struct with either a float or a double to vary precision
	template <class sp_or_dp>
		struct CellData
	{
		typedef sp_or_dp value_type;
		value_type angle;
		value_type x;
		value_type y;
	
		CellData(value_type mx, value_type my, value_type ma): x(mx), y(my), angle(ma) {};
		CellData(): x(0), y(0), angle(0) {};

		static CellData<value_type> Create_xya(value_type mx, value_type my, value_type ma)
		{
			return CellData(mx,my,ma);
		}

		static CellData<value_type> CreateRandom(MTRand& rng)
		{
			return CellData(rng.rand(), rng.rand(), rng.rand());
		}
	};

	typedef MACRO_CELLTYPE Unit;
	typedef std::vector<Unit> Vector;

	


}
