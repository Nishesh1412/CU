//============================================================================
// Name        : big_number.cpp
// Author      : Nishesh Shukla
// Version     : 4.0
// Copyright   :
// Description : Samuel(LA), Dan, David Olson, Jorel Akers helped me out
//============================================================================

#include "big_number.h"
#include <math.h>

using namespace std;

// default constructor, creates a 0
big_number::big_number()
{
	head_ptr = new node;
	head_ptr -> data = '0';
	head_ptr -> next = head_ptr -> prev = nullptr;
	tail_ptr = head_ptr;
	digits = 1;
	positive = true;
	base = 10;
}

// int constructor; create big_number from base 10 integer
big_number::big_number(int i)
{
	digits = 0;
	head_ptr = new node;
	tail_ptr = head_ptr;
	head_ptr -> next = head_ptr -> prev = nullptr;
	base = 10; // assume decimal
	positive = true;
	
	if (i == 0)
	{
		head_ptr -> data = '0';
		digits = 1;
		return;
	}
	if (i < 0) 
	{
		positive = false;
		i *= -1;
	}
	
	head_ptr -> data = i % 10 + '0';
	i /= 10;
	++digits;
	
	while (i > 0)
	{
		head_ptr -> prev = new node;
		head_ptr -> prev -> data = (i % 10) + '0';
		head_ptr -> prev -> next = head_ptr;
		head_ptr = head_ptr -> prev;
		head_ptr -> prev = nullptr;
		++digits;
		i /= 10;
	}
}

// copy constructor, creates a deep copy of m
big_number::big_number(const big_number& m)
{
	head_ptr = nullptr;
	tail_ptr = nullptr;
	*this = m;
}

// conversion constructor; convert m to a different base
big_number::big_number(const big_number& m, unsigned int b)
{
	head_ptr = tail_ptr = nullptr;
	positive = m.positive;
	
	big_number zero;
	zero.base = b;
	*this = zero;
	unsigned int digit;
	
	big_number* values = new big_number[m.base + 1];
	
	big_number j = 0;
	j.base = b;
	
	for (unsigned int i = 0; i <= m.base; ++i)
	{
		values[i] = j;
		++j;
	}
	
	for (const node* cursor = m.head_ptr; cursor != nullptr;
		cursor = cursor -> next)
	{
		if (isdigit(cursor -> data))
			digit = cursor -> data - '0';
		else
			digit = cursor -> data - 'a' + 10;
		big_number intermed = values[m.base] * (*this);
		if (intermed > zero)
		{
			intermed.sum(values[digit]);
		}
		else 
		{
			big_number temp(intermed);
			intermed = values[digit];
			intermed += temp;
		}
		*this = intermed;
	}	
	delete [] values;
}

// create a big_number from a string
big_number::big_number(const string& s, unsigned int b)
{
	digits = 0;
	head_ptr = new node;
	head_ptr -> next = head_ptr -> prev = nullptr;
	tail_ptr = head_ptr;
	base = b;
	unsigned int index = 0;
	positive = true;
	if (s[0] == '+')
		++index;
	if (s[0] == '-') 
	{
		positive = false;
		++index;
	}
	head_ptr -> data = s[index++];
	++digits;
	node* cursor = head_ptr;
	while (index < s.length())
	{
		cursor -> next = new node;
		cursor -> next -> data = s[index++];
		cursor -> next -> next = nullptr;
		cursor -> next -> prev = cursor;
		cursor = cursor -> next;
		++digits;
	}	
}

// destructor
big_number::~big_number()
{
	clear_list(head_ptr, tail_ptr);
}

// assignment operator
big_number& big_number::operator=(const big_number& m)
{
	if (this == &m) return *this;
	base = m.base;
	copy_list(m.head_ptr, head_ptr, tail_ptr);
	positive = m.positive;
	digits = m.digits;
	return *this;
}

// set value to original value + b; return answer in original number's base
big_number& big_number::operator+= (const big_number& b) // PART 2 (DONE)
{
	trim(); //trim the 0s infront at first
	big_number n1(*this); big_number n2(b);//assign them to different ones.
	n2.trim();
	n1.positive = true;
	n2.positive = true;
	if(n1 < n2) //case 1
	{
		std::swap(n1,n2);
		n1.positive = b.positive;
	}
	else //case 2
		n1.positive = positive;
	if(positive != b.positive) //case 3
		n1.diff(n2);
	else //case 4
		n1.sum(n2);
	*this = n1; trim(); // after the addition trim the 00s created infront by the sum operatotr.
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator*= (const big_number& b)// PART 2 (DONE)
{
	big_number n1 = mult(b); // use the helper multiplication function, this should be sufficient.
	*this = n1;
	return *this;
}

// set value to original value - b; return answer in original number's base
big_number& big_number::operator-= (const big_number& b)// PART 2 (DONE)
{
	big_number n1(b);
	n1.positive = !n1.positive; // opposite of sum
	*this += n1;
	return *this;
}

// set value to original value / b; return answer in original number's base
big_number& big_number::operator/= (const big_number& b)// PART 2 (DONE)
{
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator%= (const big_number& b)
{
	return *this;
}

// prefix increment
big_number& big_number::operator++()// PART 2 (DONE)
{
	big_number temp('1');
	*this += temp;
	return *this;
}

// prefix decrement
big_number& big_number::operator--()// PART 2 (DONE)
{
	big_number temp('1');
	*this -= temp;// opposite of increment prefix
	return *this;
}

// assume same base, |*this| > |b|
big_number& big_number::sum(const big_number& b)// PART 2 (DONE)
{
	node* cursor = tail_ptr;
	const node* bcursor = b.tail_ptr;
	digits = 0;  // alert, dangerous territory
	unsigned int dig1, dig2, result;
	unsigned int carry = 0;
	while (cursor != nullptr && bcursor != nullptr)
	{
		dig1 = alpha.find(cursor -> data); // added to the header file
		dig2 = alpha.find(bcursor -> data);
		result = carry + dig1 + dig2;
		if (result >= base) // need to carry
		{
			cursor -> data = alpha[result % base];
			carry = 1;
		}
		else // 0 carry
		{
			cursor -> data = alpha[result];
			carry = 0;
		}
		cursor = cursor -> prev;
		bcursor = bcursor -> prev;
		++digits;
	}
	while (cursor != nullptr)
	{
		dig1 = alpha.find(cursor -> data);
		result = carry + dig1;
		if (result >= base) // need to carry
		{
			cursor -> data = alpha[result % base];
			carry = 1;
		}
		else // 0 carry
		{
			cursor -> data = alpha[result];
			carry = 0;
		}
		cursor = cursor -> prev;
		++digits;
	}
	
	if (carry > 0)
	{
		head_ptr -> prev = new node;
		head_ptr -> prev -> prev = nullptr;
		head_ptr -> prev -> next = head_ptr;
		head_ptr -> prev -> data = '1';
		++digits;
		head_ptr = head_ptr -> prev;
	}
	return *this;
}

// assume same base, |*this| > |b|
big_number& big_number::diff(const big_number& b)// PART 2 (DONE)
{
	node* cursor = tail_ptr; //takes care of the difference function for the sum/minus/multiplication functions
	node* bcursor = b.tail_ptr;
	int val1, val2, borrow; // initialize the two ints and a borrow function for the difference, mainly for the addition and subtraction.
	borrow = 0; //starting at 0
	while ( bcursor)
	{
		val1 = alpha.find(cursor -> data); // find the specific data in the alpha string in the header file
		val2 = alpha.find(bcursor -> data);
		val1 -= val2 + borrow;
		if(val1 < 0) // as long as val1 is less than 0
		{
			val1 += base;
			borrow = 1;
		}
		else borrow = 0; // no need to borrow

		cursor -> data = alpha[val1]; // change the following values and run the while loop again
		cursor = cursor -> prev;// this way the while loop runs as long as the intial while loop condition stays true
		bcursor = bcursor -> prev;
	}
	while(cursor)
	{
		val1 = alpha.find(cursor -> data); // find the data in the string alpha in the header file
		val1 -= borrow;
		if(val1 < 0) // similar to the previous while statement
		{
			val1 += base;
			borrow = 1;
		}
		else borrow = 0; //no need to borrow, 0
		cursor -> data = alpha[val1];
		cursor = cursor -> prev;
	}
	if(borrow)
	{
		node* curr = head_ptr;
		head_ptr -> next -> prev = nullptr;
		head_ptr= head_ptr -> next;
		delete curr;
	}
	return *this;
}
		
// remove leading zeros
void big_number::trim()
{
	while (head_ptr != tail_ptr && head_ptr -> data == '0')
	{
		--digits;
		head_ptr = head_ptr -> next;
		delete head_ptr -> prev;
		head_ptr -> prev = nullptr;
	}
}

// friend for comparing digits
int cmp(const big_number& a, const big_number& b)
{
	if (a.digits > b.digits) return 1;
	if (a.digits < b.digits) return -1;
	const node* a_cursor;
	const node* b_cursor;
	for (a_cursor = a.head_ptr, b_cursor = b.head_ptr; 
		b_cursor != nullptr && a_cursor -> data == b_cursor -> data;
		b_cursor = b_cursor -> next, a_cursor = a_cursor -> next)
		;
	if (a_cursor == nullptr) return 0;
	if (a_cursor -> data > b_cursor -> data) return 1;
	return -1;
}

bool operator >(const big_number& a, const big_number& b)
{
//	big_number temp_b(b, a.base);
	if (a.positive && !b.positive)
		return true;
	if (!a.positive && b.positive)
		return false;
	if (a.positive)
		return cmp(a, b) > 0;
	else
		return cmp(a, b) < 0;
	return false;
}

bool operator >=(const big_number& a, const big_number& b)
{
//	big_number temp_b(b, a.base);
	if (a.positive && !b.positive)
		return true;
	if (!a.positive && b.positive)
		return false;
	if (a.positive)
		return cmp(a, b) >= 0;
	else
		return cmp(a, b) <= 0;
	return true;
}

bool operator <(const big_number& a, const big_number& b)
{
//	big_number temp_b(b, a.base);
	if (a.positive && !b.positive)
		return false;
	if (!a.positive && b.positive)
		return true;
	if (a.positive)
		return cmp(a, b) < 0;
	else
		return cmp(a, b) > 0;
	return false;
}
			
bool operator <=(const big_number& a, const big_number& b)
{
//	big_number temp_b(b, a.base);
	if (a.positive && !b.positive)
		return false;
	if (!a.positive && b.positive)
		return true;
	if (a.positive)
		return cmp(a, b) <= 0;
	else
		return cmp(a, b) >= 0;
	return true;
}
			
bool operator==(const big_number& a, const big_number& b)
{
//	big_number temp_b(b, a.base);
	if (a.positive != b.positive) return false;
	
	return cmp(a, b) == 0;
}
	
bool operator!=(const big_number& a, const big_number& b)
{
	return !(a == b);
}

ostream& operator <<(ostream& out, const big_number& n)
{
	if (!n.positive) out << '-';
	for (const node* cursor = n.head_ptr; cursor != nullptr; cursor = cursor -> next)
			out << cursor -> data;
	out << "(" << n.base << ")";
	return out;
}

istream& operator >>(istream& in, big_number& n)
{
	unsigned int base;
	cout << "Enter a base: ";
	cin >> base;
	cout << "Enter a number: ";
	string babin;
	in >> babin;
	
	big_number baboo(babin, base);
	n = baboo;
	return in;
}

big_number operator+(const big_number& a, const big_number& b)// PART 2 (DONE)
{
	big_number answer;
	answer += a; // sum function already defined with the sum helper function and the += above/below
	answer += b;
	return answer;
}

big_number operator-(const big_number& a, const big_number& b)// PART 2 (DONE)
{
	big_number answer; // opposite of the sum fucntion
	answer -= a;
	answer -= b;
	return answer;
}

big_number operator*(const big_number& a, const big_number& b)// PART (DONE)
{
	big_number answer;//uses the helper function initailize below, now its just plug and play.
	answer *= a;
	answer *= b;
	return answer;
}

big_number factorial(const big_number& a)
{
	big_number answer;
//	big_number c;
//	while (a != 0){
//		big_number top = mult(a);
//		c = a -1;
//		big_number bottom = mult(c);
//		big_number answer = a * c;
//	}
	return answer;
}

big_number big_number::mult(const big_number& b)const// PART 2 (DONE)
{
	big_number n1(*this); big_number n2(b); big_number result; big_number inter;// initialize all big nums
	node* cursor; node* icursor; // cursors to copy/keep track
	node* b_cursor = n2.tail_ptr;
	int val1, val2, carry; // initalize two different numbers and carry
	int basepwr = 1; // starting off with 1
	int i; // initalize int 1 to use in the for loop.
	carry = 0;
	while(b_cursor)
	{
		val2= alpha.find(b_cursor -> data); // using the string in the header file, finding a specific letter/number in the given alpha string
		cursor = n1.tail_ptr; // set cursor to n1's tail_ptr
		inter = big_number();
		for(i = 1;i < basepwr; ++i)
		{
			inter.head_ptr -> prev = new node;
			inter.head_ptr -> prev -> data = '0';
			inter.head_ptr -> prev -> next = inter.head_ptr;
			inter.head_ptr -> prev -> prev = nullptr;
			inter.head_ptr = inter.head_ptr -> prev;
			++inter.digits;
		}
		icursor = inter.head_ptr;
		while(cursor)
		{
			if(!icursor)
			{
				icursor = new node;// initialize icursor again
				icursor -> prev = nullptr;//start it from the begining at where head_ptr is pointing to
				icursor -> next = inter.head_ptr;
				inter.head_ptr -> prev = icursor;
				inter.head_ptr = icursor;
				++inter.digits;//increment the digits for the while loop
			}
			val1 = alpha.find(cursor -> data); //find the matching data in the string in the header file
			val1 = val1 * val2 + carry; // multiplication
			icursor -> data = alpha[val1 % base]; //making sure the first and two digits including the carry are well taken care of.
			carry= val1 / base; // with the base and the modulus function
			cursor = cursor -> prev; // set it to the previous so that the while loop continues to run with different data's as long as the initail condition stays true
			icursor = icursor -> prev;
		}
		result += inter;
		b_cursor = b_cursor -> prev;
		++basepwr;// increasing the basepower as the while loop ends
	}
	if (carry) // takes care of the carry
	{
		result.head_ptr -> prev = new node;
		result.head_ptr -> prev -> next = result.head_ptr;
		result.head_ptr -> prev -> data = alpha[carry];
		result.head_ptr = result.head_ptr -> prev;
	}
	result.positive =(positive == b.positive);
	return result;
}
