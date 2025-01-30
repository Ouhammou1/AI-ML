#include <iostream>


int main()
{

	int n = 2000;
	int *ptr = &n;

	std::cout << n << std::endl;
	std::cout << &n << std::endl;
	std::cout << ptr << std::endl;
	return 0;
}