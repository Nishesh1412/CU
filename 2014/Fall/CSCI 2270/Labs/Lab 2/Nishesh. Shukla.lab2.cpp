#include <iostream>

using namespace std;

int main() {

	unsigned int array_size; // upper limit of numbers to check for primes

	cout << "Find primes from 0 to what? "; // ask user for upper limit
	cin >> array_size; // get size from user
	
	if (array_size <= 1) {
		cout << "There are no primes between 0 and " << array_size<< "." << endl;
		return 0;
	}
	
	array_size++; // add one slot for 0 to the size

	bool prime_numbers[array_size]; // make the bool array for

	// assume all the rest are primes
	// remove 0, 1 from primes
	for (unsigned int i = 2; i < array_size; i++) {
		prime_numbers[i] = true;
	}

	unsigned int counter = 2;
	
	prime_numbers[0] = false; //setting 0 and 1 to false. non-prime numbers
	prime_numbers[1] = false; 
	
	
	// mark all multiples of a new true prime_number as false (not primes)
	while (counter < array_size) {
		if (prime_numbers[counter]) {
			for (unsigned int x = counter; counter * x < array_size; x++) {
				prime_numbers[counter * x] = false;
			}
		}
		counter++;
	}

	// print the whole array -> all primes are printed with a 1.
	for (unsigned int k = 0; k < array_size; k++)
		if (prime_numbers[k] == true){
		cout << k << " " << endl;
	}

}
