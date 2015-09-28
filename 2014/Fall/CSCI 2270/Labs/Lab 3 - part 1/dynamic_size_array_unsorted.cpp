#include "dynamic_size_array_unsorted.h"

using namespace std;


void init(int_array& arr)
{
	arr.capacity = arr.DEFAULT_CAPACITY;
	arr.data = new int [arr.capacity];
	arr.count = 0;
}

void clear(int_array& arr)
{
	void destr();
	void init(); 
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
	
	for (unsigned int i=0; i< arr.count; i++){
		if (arr.data[i] == target){
		return true;
		}
	}
	return false;
}

void resize(int_array& arr)
{
	arr.capacity *= 2;
	int *array_2 = new int [arr.capacity];
	for (unsigned int k = 0; k < arr.count; k++) {
	array_2[k] = arr.data[k];
	}
	delete [] arr.data;
	arr.data = array_2;
	
}

void add(int_array& arr, const int& payload)
{
	if (arr.count == arr.capacity){
		void resize();
		}
	cin >> arr.count;	
	arr.count++;
	
}

bool remove(int_array& arr, const int& target)
{
	for (unsigned int i=0; i< arr.count; i++) {
	if (arr.data[i] == target){
	delete arr.data[target];
	return true;
	arr.count--;
	}
	}
return false;
}

