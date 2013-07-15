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
		typedef uint uint32;

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

		RealType m_total_time;
		Vector system;
		MTRand rng;

	public:
		//RealType box_size(){ return box_size;}


		SimSystem(bool print_out=false):dt(__MC_dt_DFT),
						 v0(__MC_v0_DFT),
						 mob(__MC_mob_DFT),
						 t_relax(__MC_t_relax_DFT),
						 noise(__MC_noise_DFT),
						 box_size(__MC_box_size_DFT),
						 Fadh(__MC_Fadh_DFT),
						 Frep(__MC_Frep_DFT),
						 Req(__MC_Req_DFT),
						 Rcut(__MC_Rcut_DFT){
			m_total_time = 0;
			if (print_out){
				PrintParams();
			}
		}	

		void SetRNGSeed(int seed){
			rng = MTRand(seed);
		}
		void SetFadh(RealType n_Fadh){ Fadh = n_Fadh;}
		void SetFrep(int n_Frep){ Frep = n_Frep;}

		void PrintParams();
		
		void TimeStep();
		int EqStep();
		int Equilibrate(int n_equil);


		/// Scale all of the translational 
		void LinearZoom(double zoom_factor);

		void RandomizeAngles();
		// All angles are aligned
		void GenerateCubicLattice(unsigned int n_in_length);
		void GenerateNRandom(unsigned int N);
		void GenerateNPile(uint N, RealType x, RealType y);
		
		
		const Vector& ViewSystem(){
			return system;
		}
	};
}



#endif
