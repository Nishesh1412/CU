#include <iostream>
#include <algorithm>

using namespace std;

void copy_array() 
{
	int* arr1 = new int[10];
	for (unsigned int k = 0; k < 10; ++k)
		arr1[k] = k*k;
	for (unsigned int k = 0; k < 10; ++k)
		cout << arr1[k] << " ";
	cout << endl;
	int* arr2 = new int[20];
	copy(arr1, arr1 + 10, arr2);
	copy(arr1, arr1 + 10, arr2 + 10);
	for (unsigned int k = 0; k < 20; ++k)
		cout << arr2[k] << " ";
	cout << endl;
}


int main()
{
	copy_array();
}
