#ifndef __XYADATA_H__
#define __XYADATA_H__

#ifdef DP
#define MACRO_PRECISION double
#else
#define MACRO_PRECISION float
#endif


class XYAData{
	public:
		typedef MACRO_PRECISION RealType;
		typedef std::vector<RealType> XYARep;
		
		RealType angle;
		RealType x;
		RealType y;
		
		XYAData(RealType mx, RealType my, RealType ma): angle(ma), x(mx), y(my), Fx(0), Fy(0) {};
		XYAData(): angle(0), x(0), y(0), Fx(0), Fy(0) {};



		// Must be templated with a subclass for functionality
		template <class XYADataType>
		static XYADataType Create_xya(RealType mx, RealType my, RealType ma){
			return XYADataType(mx,my,ma);
		}

		// Must be templated with a subclass for functionality
		template <class XYADataType>
		static XYADataType Create_xy(RealType mx, RealType my){
			return XYADataType(mx,my,0);
		}
};

/// Templated class must be a subclass of XYAData
template <class XYADataType>
class XYAVec
{
	typedef std::vector<XYADataType> TypedVec;
	using XYAData::RealType;

	static void GenerateXYA(TypedVec& data, RealType x, RealType y, RealType a){
		data.push_back(Create_xya<XYADataType>(x,y,a));
	}

	// Must return by value because the return is going out of scope
	static XYARep GetXYARep(TypedVec& data){
		XYARep out;
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
