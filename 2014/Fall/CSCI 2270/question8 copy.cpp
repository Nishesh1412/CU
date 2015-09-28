#include <iostream>

using namespace std;

// inputs: a string s
bool is_palindrome(const string& s)
{
	if (s.length() == 1){ // checks if the string only has one letter, if it does it returns true.
	return true; // if not it moves on to the else function
	}
	else {
		int inital = 0; //setting up a comparison between the first and last
		int final = s.length() - 1;
		while (inital < final){ // going through
			if (s[inital] != s[final]) return false;
			++inital;
			--final;
		}
		return true;
	}
}

// inputs: a string s, an index into a letter near the front of s, and a 
// letter near the back of s
bool is_palindrome_recursive(const string& s, 
	const unsigned int& start, const unsigned int& end)
{
	if (s.length() == 1) {
	return true;
	}
	if (start >=end) return true;
	if (s[start] != s[end]) return false;
	return is_palindrome_recursive(s, start+1 , end--);
}

int main()
{
	string b = "q";
	string c = "bob";
	string d = "anna";
	string e = "banana";
	string f = "abcddcba";
	string g;
	
	if (is_palindrome(b) && is_palindrome(c) &&
		is_palindrome(d) && !is_palindrome(e) && is_palindrome(f))
	{
		cout << b << " " << "is a palindrome" << endl;
		cout << c << " " << "is a palindrome" << endl;
		cout << d << " " << "is a palindrome" << endl;
		cout << e << " " << "is not a palindrome" << endl;
		cout << f << " " << "is a palindrome" << endl;
	}
	
	if (is_palindrome_recursive(b, 0, b.length() - 1) && 
		is_palindrome_recursive(c, 0, c.length() - 1) &&
		is_palindrome_recursive(d, 0, d.length() - 1) && 
		!is_palindrome_recursive(e, 0, e.length() - 1) && 
		is_palindrome_recursive(f, 0, f.length() - 1))
	{
		cout << b << " " << "is a palindrome" << endl;
		cout << c << " " << "is a palindrome" << endl;
		cout << d << " " << "is a palindrome" << endl;
		cout << e << " " << "is not a palindrome" << endl;
		cout << f << " " << "is a palindrome" << endl;
	}
	
	cout << "Enter a string to check: ";
	cin >> g;
	if (is_palindrome(g) && is_palindrome_recursive(g, 0, g.length() - 1))
		cout << g << " " << "is a palindrome" << endl;
	else if (!is_palindrome(g) && !is_palindrome_recursive(g, 0, g.length() - 1))
		cout << g << " " << "is not a palindrome" << endl;
	else
		cout << "Inconsistent results on your string" << endl;
	
}
