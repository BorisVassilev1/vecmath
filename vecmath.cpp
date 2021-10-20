#include "vecmath.h"

int main() {
	vecmath::vec<2, float> a(1, 3), b(-2., -3.);
	std::cout << a << std::endl << b << std::endl;
	vecmath::vec<2, float> c(1.f, 2.f);
	std::cout << c << std::endl << a + c << std::endl <<  a / c << std::endl;
	
	a += b;
	std::cout << a << std::endl;

	a += a[0];
	
	std::cout << (vecmath::vec<2, float>(1, 1) == vecmath::vec<2, float>(2, 1)) << std::endl;
	
	++ a;
	std::cout << a ++ << std::endl << a << std::endl;
	
	a[1] ++;

	
	std::cout << sin(a) << std::endl;

	exp(a);
	exp2(a);

}
