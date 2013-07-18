#ifndef __XYADATA_H__
#define __XYADATA_H__

/*-------------------------------------------------------------
 * xyadata.h:
 * 	XYAData base class
 * 	XYAVec templated class
 * 	XYAConst namespace
 *
 * RULES not specified by compiler:
 * 	1. Children of XYAData must define their constructor(Realtype mx, RealType my, RealType ma)
 *
 *
 */



#ifdef DP
#define MACRO_PRECISION double
#else
#define MACRO_PRECISION float
#endif

#include <vector>

class XYAData{
	public:
		typedef MACRO_PRECISION RealType;
		typedef std::vector<RealType> XYARep;
		
		RealType angle;
		RealType x;
		RealType y;
		
		// Subclasses are REQUIRED to define this constructor
		XYAData(RealType mx, RealType my, RealType ma): angle(ma), x(mx), y(my) {}
		XYAData(): angle(0), x(0), y(0) {}


		// Must be templated with a subclass of this (XYAData)
		template <class XYADataType>
		static XYADataType Create_xya(RealType mx, RealType my, RealType ma){
			return XYADataType(mx,my,ma);
		}

		// Must be templated with a subclass of this (XYAData)
		template <class XYADataType>
		static XYADataType Create_xy(RealType mx, RealType my){
			return XYADataType(mx,my,0);
		}
};

/// Templated class must be a subclass of XYAData
template <class XYADataType>
class XYAVec
{
	public:
		typedef std::vector<XYADataType> TypedVec;
		typedef XYAData::RealType RealType;

		static void GenerateXYA(TypedVec& data, RealType x, RealType y, RealType a){
			data.push_back(XYAData::Create_xya<XYADataType>(x,y,a));
		}

		// Must return by value because the return is going out of scope
		static XYAData::XYARep GetXYARep(TypedVec& data){
			XYAData::XYARep out;
			for (auto xya : data){
				out.push_back(xya.angle);
				out.push_back(xya.x);
				out.push_back(xya.y);
			}
			return out;
		}
};


namespace XYAConst{
	static XYAData::RealType twoPi = 2 * 3.14159265359;
}


#endif //__XYADATA_H__
