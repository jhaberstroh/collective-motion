#ifndef __TISSUESIMULATION_H_DEFINED__
#define __TISSUESIMULATION_H_DEFINED__

#include "xyasimulation.h"
#include "xyadata.h"

#define __MC_v0_DFT 1
#define __MC_mob_DFT 1
#define __MC_t_relax_DFT 1
#define __MC_noise_DFT 0
#define __MC_box_size_DFT 10
#define __MC_Fadh_DFT .75
#define __MC_Frep_DFT 3
#define __MC_Req_DFT 1
#define __MC_Rcut_DFT 2


class TissueCell : public XYAData{
	public:
		typedef XYAData::RealType RealType;
		RealType Fx;
		RealType Fy;

		// Required constructor from XYAData
		TissueCell(RealType mx, RealType my, RealType ma): XYAData(mx,my,ma), Fx(0), Fy(0){}
		TissueCell(): XYAData(), Fx(0), Fy(0){}

		int TakeStep(RealType dt, RealType v0, RealType mob, RealType t_relax, RealType noise, RealType box_size, MTRand& rng, bool eq=false);
		RealType Interact(TissueCell& cell2, RealType r_cut, RealType r_eq, RealType box_size, RealType F_adh, RealType F_rep);
		void CheckRep(RealType box_size);
		void print();
};


class TissueSimulation : public XYASimulation<TissueCell>{
	private:
		typedef XYASimulation<TissueCell> XYASim;
		typedef XYAData::RealType RealType;

		/// Movement parameters
		RealType dt;
		RealType v0;
		RealType mob;
		RealType t_relax;
		RealType noise;

		/// Force parameters
		RealType Fadh;
		RealType Frep;
		RealType Req;
		RealType Rcut;

		RealType m_total_time;

	public:
		//RealType box_size(){ return box_size;}

		TissueSimulation(bool print_out=false):
						 XYASim(),
						 v0(__MC_v0_DFT),
						 mob(__MC_mob_DFT),
						 t_relax(__MC_t_relax_DFT),
						 noise(__MC_noise_DFT),
						 Fadh(__MC_Fadh_DFT),
						 Frep(__MC_Frep_DFT),
						 Req(__MC_Req_DFT),
						 Rcut(__MC_Rcut_DFT){
		// Overwrite m_box_size default in XYASimulation
		 m_box_size = __MC_box_size_DFT;
			if (print_out){
				PrintParams();
			}
		}	

// Extended function definition
		void PrintParams();
		void LinearZoom(RealType zoom_factor);
// Virtual function definitions
		virtual void TimeStep();

		void SetFadh(RealType n_Fadh){ Fadh = n_Fadh;}
		void SetFrep(int n_Frep){ Frep = n_Frep;}
		void Setdt(RealType n_dt){ dt = n_dt;}

		//int EqStep();
		//int Equilibrate(int n_equil);
};



#endif
