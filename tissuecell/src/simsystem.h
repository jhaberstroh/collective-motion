#ifndef __TISSUECELL_SYSTEM_H_DEFINED__
#define __TISSUECELL_SYSTEM_H_DEFINED__

#include "tissuecell.h"

#define __MC_dt_DFT 1
#define __MC_v0_DFT 1
#define __MC_mob_DFT 1
#define __MC_t_relax_DFT 1
#define __MC_noise_DFT 0
#define __MC_box_size_DFT 10
#define __MC_Fadh_DFT .75
#define __MC_Frep_DFT 30
#define __MC_Req_DFT 1
#define __MC_Rcut_DFT 2


namespace TissueCell{

	class SimSystem{
	private:
		/// Movement parameters
		RealType dt;
		RealType v0;
		RealType mob;
		RealType t_relax;
		RealType noise;
		RealType box_size;

		/// Force parameters
		RealType Fadh;
		RealType Frep;
		RealType Req;
		RealType Rcut;

	public:
		void PrintParams();

		SimSystem():dt(__MC_dt_DFT),
						 v0(__MC_v0_DFT),
						 mob(__MC_mob_DFT),
						 t_relax(__MC_t_relax_DFT),
						 noise(__MC_noise_DFT),
						 box_size(__MC_box_size_DFT),
						 Fadh(__MC_Fadh_DFT),
						 Frep(__MC_Frep_DFT),
						 Req(__MC_Req_DFT),
						 Rcut(__MC_Rcut_DFT){
			PrintParams();
		}	
		
		using namespace std
		void myfun(){
			vector x

			x.append(thing)

		}
			std::vector
			TissueCell::vector
	}


}



#endif
