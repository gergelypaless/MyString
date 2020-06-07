#include <iostream>

#include "mystring.h"

int main()
{
	// test program
	MyString a = "hello";
	MyString b = a;
	std::cout << b[1] << std::endl;          /* e */
	
	a[1] = 'a';
	b[1] = b[4];
	std::cout << a << " " << b; /* hallo hollo */
	
	std::cin.get();
	return 0;
}
