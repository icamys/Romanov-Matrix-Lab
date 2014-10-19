#include "matrix.hpp"
#include <iostream>

int main() {
	double testArray[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	Matrix m(2, 3, testArray);

	//printf("%f %f %f\n", m[0][0], m[0][2], m[1][1]);
	//std::cout << m[0][2];
	std::cout << testArray;
	return 0;
}