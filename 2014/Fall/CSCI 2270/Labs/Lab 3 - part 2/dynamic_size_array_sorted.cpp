// Nishesh Shukla
//Jorel Akers helped me out!
//09/20/14

#include "dynamic_size_array_sorted.h"

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
	delete arr.data;
	arr.count = 0;
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


void print(const int_array& arr)
{
	for (unsigned int i = 0; i < arr.count; ++i)
		cout << arr.data[i] << " ";
	cout << endl;
}

void add(int_array& arr, const int& payload)//
{
	if (arr.count == arr.capacity){
		void resize();
		}
	if (arr.count ==0){
		arr.data[arr.count] = payload;
		arr.count ++;
	}
	else
	{
		arr.data[arr.count] = payload;
		arr.count++;
		for (unsigned int i = 1; i < arr.count; ++i){
			unsigned j = i;
			while (j>0 && arr.data[j] < arr.data[j-1]) {
				int temporary = arr.data[j];
				arr.data[j] = arr.data [j-1];
				arr.data [j-1] = temporary;
				j--;
			}
		}
	}
}

bool remove(int_array& arr, const int& target)//
{
	unsigned int j = 0;

	while (j < arr.count){
		if (arr.data[j] == target){
			unsigned int b = j;
			while (b < arr.count){
				arr.data[b] = arr.data [b + 1];
				b++;
			}
			arr.count = arr.count -1;
			return true;
		}
		j++;
	}
	return false;
}

bool contains(const int_array& arr, const int& target)
{
	
	for (unsigned int i=0; i< arr.count; i++){
		if (arr.data[i] == target){
		return true;
		}
		else {
			i++;
		}
	}
	return false;
}

