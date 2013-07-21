#ifndef __NEMATICSIM_H_DEFINED__
#define __NEMATICSIM_H_DEFINED__


#include "xyasimulation.h"

class NematicSim : public XYASimulation<XYAData>
{
	RealType cutoff;
	RealType noise;
	RealType velocity;

	NematicSim():
		XYASimulation<XYAData>(),
		cutoff(1.5),
		noise(.1),
		velocity(1)
	{}

	virtual void TimeStep();

	//typename XYAVec<XYADataType>::TypedVec m_sim_data;
	//MTRand m_rng;
	//RealType m_box_size;
	//RealType dt;
}



#endif //__NEMATICSIM_H_DEFINED__
