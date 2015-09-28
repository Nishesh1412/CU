#include <iostream>
using namespace std;

// scale every number in an array by a factor of 3
void triple_an_array_1(int* starting_array, unsigned int size)
{
	// we pass in a copy of the address of 	
	// starting_array
	// and then we triple every item in the array
	for (unsigned int k = 0; k < size; ++k)
		// this line dereferences starting_array
		starting_array[k] *= 3;	
}	

// replace an array with an array that has 3 copies of the 
// original numbers
void triple_an_array_2(int*& starting_array, unsigned int size)
{
  	// we pass in the location of the pointer 
	// to the starting array
	int* triple_array = new int[3 * size];
	for (unsigned int k = 0; k < 3 * size; ++k)
		triple_array[k] = 
			starting_array[k % size];
	delete [] starting_array;
	starting_array = triple_array;
}

/*    
void triple_an_array_3(const int*& starting_array, unsigned int size)
{
	for (unsigned int k = 0; k < size; ++k)
		starting_array[k] *= 3;			// NO
}
*/

void print_an_array(const int*& starting_array, unsigned int size)
{
	for (unsigned int k = 0; k < size; ++k)
		cout << starting_array[k] << " ";
	cout << endl;			// NO
}

int main()
{
	int* lebowski = new int[10];
	int* bob = new int[10];
	for (unsigned int k = 0; k < 10; ++k)
	{	
		lebowski[k] = 2*k; 
		bob[k] = 3*k;		
	}
	cout << "before function" << endl;
	for (unsigned int k = 0; k < 10; ++k)
		cout << lebowski[k] << " ";
	cout << endl;
	triple_an_array_1(lebowski, 10);
	cout << "after function" << endl;
	for (unsigned int k = 0; k < 10; ++k)
		cout << lebowski[k] << " ";
	cout << endl;
	cout << "before function" << endl;
	for (unsigned int k = 0; k < 10; ++k)
		cout << bob[k] << " ";
	cout << endl;
	triple_an_array_2(bob, 10);
	cout << "after function" << endl;
	for (unsigned int k = 0; k < 30; ++k)
		cout << bob[k] << " ";
	cout << endl;
}
