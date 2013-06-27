#include "tissuecell.h"

int main(){
	TissueCell::Unit x = TissueCell::Unit::Create_xya(1.3, 1.3, 3.14);
	TissueCell::Vector myvector(10, x);
	std::cout << typeid(myvector[5].x).name() << std::endl;
}
