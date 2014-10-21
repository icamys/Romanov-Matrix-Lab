#include "matrix.hpp"
#include <stdexcept>
#include <iostream>

int main() {
	double testArray1[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	double testArray2[] = { 1.0, 3.0, 3.0, 4.0, 5.0, 6.0 };
	Matrix m1(2, 3, testArray1);
	Matrix m2(2, 3, testArray2);
    Matrix r = Matrix(5, 5);

//	printf("%f %f %f\n", m[0][0], m[0][2], m[1][1]);
//	std::cout << m[0][2];
    
	try 
    {
        r = m1 + m2;
        std::cout << r;
    } 
    catch (Matrix::Exception* e) 
    {
        std::cout << e->what() << std::endl;
    }
    catch (std::exception* e) 
    {
        std::cout << e->what() << std::endl;
    }
    
	return 0;
}