#include <iostream>
#include <vector>

// Create the data struct with either a float or a double to vary precision
template <class Precision>
	struct Data
{
	typedef Precision value_type;
	value_type angle;
	value_type x;
	value_type y;
	Data(value_type mx, value_type my, value_type ma)
	{
		x = mx;
		y = my;
		angle = ma;
	}
};


int main(){
	typedef Data<float> mydat;
	std::vector<mydat> myvector(10,mydat(1.3, 1.3, 10));
	std::cout << myvector[5].x << std::endl;
}
