#include <cctype>          // Provides toupper
#include <iostream>        // Provides cout and cin
#include <cstdlib>         // Provides EXIT_SUCCESS
#include <string>
using namespace std;


// PROTOTYPES for functions used by this test program:
void pattern(ostream& outs, unsigned int n, unsigned int i);

int main()
{
  int i2;
  cout << "Enter an integer (a power of 2): ";
  cin >> i2;
  pattern(cout, i2, 0);
  return (EXIT_SUCCESS);
}

// i is the offset
// n is the asterisks
void pattern(ostream& outs, unsigned int n, unsigned int i)
{
	if (n == 0) return;
	if (n != 1 && n%2 != 0) cout << "Entered number is not a result of power of 2"<< endl;
	else {
		pattern (cout, n/2, i);
		for (unsigned int k = 0; k < i; k++){
			cout << " ";
		}
		for (unsigned int j = 0; j < n; j++){
			cout<< "*";
		}
		cout << endl;
		pattern (cout, n/2, n/2 + i);
	}
}


