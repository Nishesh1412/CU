#include <iostream>

using namespace std;

bool binary_contains1(const int* arr, unsigned int first, 
	unsigned int last, int target)
{
	cout << "Searching first " << first << " to last " << last << endl;
	// base cases come first...
	if (first == last)
	{
		if (arr[first] == target)
			cout << "Success!" << endl;
		else
			cout << "Failure! " << endl;
		return (arr[first] == target);
	}
	// base case, not found
	if (first > last)
	{
		cout << "Failure!"<< endl;
		return false;
	}
	unsigned int mid = first + (last - first) / 2 ;
	// base case, found
	if (arr[mid] == target)
	{
		cout << "Success!" << endl;
		return true;
	}
	if (arr[mid] > target)
		return binary_contains1(arr, first, mid - 1, target);
	return binary_contains1(arr, mid + 1, last, target);
}  

bool binary_contains2(const int* arr, unsigned int size, int target)
{
	if (size == 0) return false;
	int middle_element = *(arr + (size/2));
	if (middle_element == target) return true;
	if (middle_element > target)
		return binary_contains2(arr, size/2, target);
	else
		return binary_contains2(arr + (size/2) + 1, size - size/2 - 1,
			target);
	return false;
}

int main()
{
	int target;
	int array[10] = {1, 6, 17, 22, 24, 26, 27, 35, 51, 98};
	for (unsigned int k = 0; k < 10; ++k)
		cout << array[k] << " ";
	cout << endl;
	cout << "Enter a number to search for: ";
	cin >> target;
	if (binary_contains1(array, 0, 9, target))
		cout << "target " << target << " found" << endl;
	else
		cout << "target " << target << " not found" << endl;
	if (binary_contains2(array, 10, target))
		cout << "target " << target << " found" << endl;
	else
		cout << "target " << target << " not found" << endl;
		
}
