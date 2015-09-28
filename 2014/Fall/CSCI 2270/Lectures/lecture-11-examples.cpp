#include <iostream>
using namespace std;

unsigned int factorial1(unsigned int n, unsigned int accumulator)
{ 
	if (n == 0) 
		return accumulator; 
	return factorial1(n - 1, n * accumulator); 
} 

unsigned int factorial(unsigned int n)
{ 
	return factorial1(n, 1); 
}

int main()
{
	cout << factorial(10) << endl;
}
