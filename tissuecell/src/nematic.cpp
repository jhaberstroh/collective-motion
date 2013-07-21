#include "nematic.h"
#include <cmath>
#include <vector>

void NematicSim::TimeStep(){
	unsigned int i,j;
	std::vector<XYAData> m_sim_copy(m_sim_data);
	
	for(i=1;i<=m_sim_data.size();i++){

			m_sim_copy[i].x=0;
		  m_sim_copy[i].y=0;

			for(j=i+1;j<=m_sim_data.size();j++){
					RealType dx = m_sim_data[j].x - m_sim_data[i].x;
					RealType dy = m_sim_data[j].y - m_sim_data[i].y;
					RealType distance = sqrt(dx * dx + dy * dy);

					if(distance<cutoff){
						if (std::cos(m_sim_data[j].angle - m_sim_data[i].angle) > 0){
							m_sim_copy[i].x += std::cos(m_sim_data[j].angle);
							m_sim_copy[i].y += std::cos(m_sim_data[j].angle);
							m_sim_copy[j].x += std::cos(m_sim_data[i].angle);
							m_sim_copy[j].y += std::cos(m_sim_data[i].angle);
						}
						else{
							m_sim_copy[i].x -= std::cos(m_sim_data[j].angle);
							m_sim_copy[i].y -= std::cos(m_sim_data[j].angle);
							m_sim_copy[j].x -= std::cos(m_sim_data[i].angle);
							m_sim_copy[j].y -= std::cos(m_sim_data[i].angle);
						}
					}
			}
			if (m_sim_copy[i].x != 0){
				m_sim_copy[i].angle = std::atan(m_sim_copy[i].y / m_sim_copy[i].x);
				if(m_sim_copy[i].x<0){
					m_sim_copy[i].angle+=M_PI;
				}
			}
			else{
				if (m_sim_copy[i].y > 0){
					m_sim_copy[i].angle = M_PI/2.;
				}
				else if (m_sim_copy[i].y < 0){
					m_sim_copy[i].angle = 3*M_PI/2.;
				}
				else{
					// Error case;
					m_sim_copy[i].angle = 0;
				}
			}
			m_sim_copy[i].angle += (m_rng.rand() - .5) * M_PI * noise;
			m_sim_copy[i].x=m_sim_data[i].x;
			m_sim_copy[i].y=m_sim_data[i].y;
			m_sim_copy[i].x+=velocity*std::cos(m_sim_copy[i].angle);
			m_sim_copy[i].y+=velocity*std::sin(m_sim_copy[i].angle);
			
	}

}
