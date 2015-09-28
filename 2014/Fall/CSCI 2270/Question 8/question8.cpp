//============================================================================
// Name        : question8.cpp
// Author      : Nishesh Shukla
// Version     : 1.0
// Copyright   :
// Description : Check for palindrome using loops and recursion
//============================================================================

#include <iostream>
using namespace std;

/**
 * Part A of the Q8.
 */
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

bool is_palindrome_recursive(const string& s, unsigned int start, unsigned int end) {

	/*
	 * Assumptions: String is never empty - therefore s.length is never < 1.
	 */

	//Step 1: Return true if only one character in string
	if (s.length() == 1) return true;

	//Step 2:
	//a) Check if recursion has reached the end, and no false return yet
	if (start >= end) return true;
	//a) Check if first and last character are the same or not
	if (s[start] != s[end]) return false;
	//c) call the parent function recursively to
	//   continue tracking first and last string chars.
	return is_palindrome_recursive(s, start+1, end-1);
	//done!
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
