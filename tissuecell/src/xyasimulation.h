#ifndef __XYASIMULATION_H__
#define __XYASIMULATION_H__

#include "xyadata.h"
#include "MersenneTwister.h"

template<class XYADataType>
class XYASimulation{
	public:
		using XYAData::RealType;
		using XYAData::XYARep;
		using XYAConst::twoPi;
		RealType dt;

	protected: 
		//Children can use protected variables, but not other code. 
		// Other code must use secified setting/getting functions, e.g. set_seed() and seed()
		int m_seed;
		MTRand m_rng;
		RealType m_total_time;
		XYAVec<XYADataType>::TypedVec m_sim_data;
		RealType m_zoom;
		RealType m_box_size;

	public:
		inline int seed(){ 
			return m_seed; 
		}
		inline void set_seed(int new_seed){
			rng.seed(new_seed);
		}
		RealType get_zoom(){ return m_zoom; }

		XYASimulation(): 
					dt(.01),
					m_box_size(10),
					m_zoom(1){
			m_seed = m_rng.rand(10000000);
			set_seed(m_seed);
		}
		XYASimulation(int seed): XYASimulation(){
			set_seed(seed)
		}
		XYARep ViewSystem(){
			return XYAVec<XYADataType>::GetXYARep(m_sim_data);
		}


		void RandomizeAngles(){
			for (auto& xya : m_sim_data){
				xya.angle = rng.rand() * twoPi;
			}
		}

		void GenerateSquareLattice(unsigned int n_in_length){
			RealType spacing = m_box_size / n_in_length;
			for (int i = 0 ; i < n_in_length; i++){
				for (int j = 0 ; j < n_in_length; j++){
					XYAVec<XYADataType>::GenerateXYA(m_sim_data, spacing * i, spacing * j);
				}
			}
		}

		void GenerateNRandom(unsigned int N){
			for (int i = 0 ; i < N ; i++){
				XYAVec<XYADataType>::GenerateXYA(m_sim_data, rand() * m_box_size, rand() * m_box_size, 0);
			}
			m_sim_data.GenerateNRandom(n_in_length);
		}

		void GenerateNPile(uint N, RealType x, RealType y){
			for (int i = 0 ; i < N ; i++){
				XYAVec<XYADataType>::GenerateXYA(m_sim_data, x, y, 0);
			}
		}

// Functions that intend extension from subclass, but does not require it.
// PrintParams() may be incomplete
		void PrintParams(){ 
			std::cout << "dt:\t" << dt << std::endl; 
		}
// LinearZoom() may need to scale parameters with dimension length
		void LinearZoom(RealType zoom_factor){
			m_box_size *= zoom_factor;
			m_zoom *= zoom_factor;
			for (auto& xya : m_sim_data){
				xya.x *= zoom_factor;
				xya.y *= zoom_factor;
			}
		}

// The only true virtual function, as it should be.
		virtual void TimeStep(){};
};


#endif //__XYASIMULATION_H__
