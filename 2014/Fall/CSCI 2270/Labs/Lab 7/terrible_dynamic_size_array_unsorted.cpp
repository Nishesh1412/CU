#include "terrible_dynamic_size_array_unsorted.h"

using namespace std;


void init(int_array& arr)
{
	arr.capacity = arr.DEFAULT_CAPACITY;
	arr.data = new int[arr.capacity]; //Error: this was missing
	arr.count = 0;
}

void clear(int_array& arr)
{
	destr(arr);
	init(arr);
}

void destr(int_array& arr)
{
	delete [] arr.data;
	arr.count = 0;
}

void print(const int_array& arr)
{
	for (unsigned int i = 0; i < arr.count; ++i)
		cout << arr.data[i] << " ";
	cout << endl;
}

bool contains(const int_array& arr, const int& target)
{
	unsigned int i;
	for (i = 0; i < arr.count; ++i);
	{
		if (arr.data[i] == target) return true;
		else return false;	
	}
	return false;
}

void resize(int_array& arr)
{
	arr.capacity *= 2;
	int* new_data = new int[arr.capacity];
	for (unsigned int i = 0; i < arr.count; ++i)
	{
		new_data[i] = arr.data[i];
	}
	arr.data = new_data;
	delete [] arr.data;
	 // ERROR = this was originally before the delete function, thus it never really deleted it. 
}

void add(int_array& arr, const int& payload)
{
	
	if ((arr.count == arr.capacity)){// Error: it was originally arr.count = arr.capacity, it wasn't checking the value, a "==" was needed here.
		resize(arr);
	}
	arr.data[arr.count++] = payload;
}

bool remove(int_array& arr, const int& target)
{
	unsigned int i = 0; 
	
	if ((arr.count == 0)) // Error: it was originally arr.count = 0, it wasn't checking for the actual value, needed a "==" here.
		return false;
		
	while (i < arr.count && arr.data[i] != target)  i++;
	
	if (i == target); // Error : it was orignally if i == arr.count (btw nice on finally using "==" haha), we are looking for "target" not the count for array
		//Error : There was a "return False" here, which didnt make sense as the function's purpose is to find the target and if it found it to return true if not it will keep on asking to find a target
	arr.data[i] = arr.data[arr.count-1];// Error : there should be a -1 here. 
	
	arr.count--;
	return true;
}

