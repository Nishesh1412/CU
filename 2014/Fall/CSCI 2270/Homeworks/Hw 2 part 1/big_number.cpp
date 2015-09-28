//============================================================================
// Name        : big_number.cpp
// Author      : Nishesh Shukla
// Version     : 2.0
// Copyright   :
// Description : Samuel Hoffman and Dr.White helped me out!
//============================================================================

#include "big_number.h"

using namespace std;

// default constructor, creates a 0
big_number::big_number()//DONE (PART 1)
{
	head_ptr = tail_ptr = nullptr;
	add_node (head_ptr,tail_ptr,'0');
	positive = true;
	base = 10;
	digits = 1;
}

// int constructor; create big_number from base 10 integer
big_number::big_number(int i)//DONE (PART 1)
{
	digits = 0;

	head_ptr = tail_ptr = nullptr;// not sure about this.
	if (i == 0){
		big_number zero;
		*this = zero;
	}
	else {
		if (i<0){
			positive = false;
			i *= -1;
		}
		else
			positive = true;
		while (i>0){
			if (head_ptr !=nullptr){
				head_ptr -> prev = new node;
				head_ptr -> prev -> data = (i % 10) + '0';
				head_ptr -> prev -> next = head_ptr;
				head_ptr = head_ptr -> prev;
			}
			else {
				head_ptr = new node;
				head_ptr -> data = (i% 10) + '0';
				tail_ptr = head_ptr;
				head_ptr -> prev = nullptr;
				head_ptr -> next = nullptr;
			}
			++digits;
			i/=10;
		}
	}
}


// copy constructor, creates a deep copy of m
big_number::big_number(const big_number& m)// DONE (PART 1)
{
	copy_list(m.head_ptr, head_ptr, tail_ptr);
	positive = m.positive;
	base = m.base;
	digits = m.digits;

}

// create a big_number from a string
big_number::big_number(const string& s, unsigned int b)//DONE (PART 1)
{

	base = 10;
	digits = 0;
	unsigned int index = 0;
	positive = true;
	if (s[0] == '-'){
		positive = false;
		++index;
	}
	if (s[0] == '+'){//if the entered number is entered with a positive sign infront of it. highly unlikely though.
			++index;
	}
	head_ptr = new node;
	head_ptr -> data = s[index++];
	head_ptr -> next = nullptr;
	head_ptr -> prev = nullptr;
	tail_ptr = head_ptr;
	++digits;
	while (index < s.length()){
		tail_ptr -> next = new node;
		tail_ptr -> next -> data = s[index++];
		tail_ptr -> next -> next = nullptr;
		tail_ptr -> next -> prev = tail_ptr;
		tail_ptr = tail_ptr -> next;
		++digits;
	}
	this -> trim();
}

// destructor
big_number::~big_number()//DONE (PART 1) //delete the entire doubly linked list(with the big numbers)
{
	clear_list(head_ptr, tail_ptr);
	digits = 0;
	positive = true;
}

// assignment operator
big_number& big_number::operator=(const big_number& m) // DONE (PART 1)
{
	if (this == &m) return *this; // self check assignment operator
	copy_list(m.head_ptr,this->head_ptr, this->tail_ptr); // create a deep copy
//	digits = m.digits;
//	positive = m.positive;
//	base = m.base;
	return *this;
}

// set value to original value + b; return answer in original number's base
big_number& big_number::operator+= (const big_number& b)
{
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator*= (const big_number& b)
{
	return *this;
}

// set value to original value - b; return answer in original number's base
big_number& big_number::operator-= (const big_number& b)
{
	return *this;
}

// set value to original value / b; return answer in original number's base
big_number& big_number::operator/= (const big_number& b)
{
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator%= (const big_number& b)
{
	return *this;
}

// prefix increment
big_number& big_number::operator++()
{
	return *this;
}

// prefix decrement
big_number& big_number::operator--()
{
	return *this;
}

bool operator >(const big_number& a, const big_number& b) {
	node * cursor_a = a.head_ptr;
	node * cursor_b = b.head_ptr;

	if (a.positive == true) {//check positives
		if (b.positive == false) // a positive and b negative means a greater than b
			return true;
		else { // both a and b are now positive
			if (a.digits > b.digits)
				return true; // a has more digits so its greater than b
			if (a.digits < b.digits)
				return false;
			while (cursor_a != nullptr && cursor_b != nullptr) {
				if ((int) cursor_a->data > (int) cursor_b->data)
					return true; // left most
				if ((int) cursor_a->data < (int) cursor_b->data)
					return false;

				cursor_a = cursor_a->next;
				cursor_b = cursor_b->next;
			}
			return false;
		}
	} else {
		if (b.positive == true)// if a is negative
			return false;
		else { // both a and b are now negative
			if (a.digits > b.digits)
				return false; // a has more digits so its less than b (because negative)
			if (a.digits < b.digits)
				return true;
			while (cursor_a != nullptr && cursor_b != nullptr) {
				if ((int) cursor_a->data > (int) cursor_b->data)
					return false;
				if ((int) cursor_a->data < (int) cursor_b->data)
					return true;

				cursor_a = cursor_a->next;
				cursor_b = cursor_b->next;
			}
			return false;
		}
	}
}

bool operator <(const big_number& a, const big_number& b) {
	node * cursor_a = a.head_ptr;
	node * cursor_b = b.head_ptr;

	if (b.positive == true) {
		if (a.positive == false) // a positive and b negative means a greater than b
			return true;
		else { // both a and b are now positive
			if (b.digits > a.digits)
				return true; // a has more digits so its greater than b
			if (b.digits < a.digits)
				return false;
			while (cursor_b != nullptr && cursor_a != nullptr) {

				if ((int) cursor_b->data > (int) cursor_a->data)
					return true; // left most
				if ((int) cursor_b->data < (int) cursor_a->data)
					return false;

				cursor_a = cursor_a->next;
				cursor_b = cursor_b->next;
			}
			return false;
		}
	} else {
		if (a.positive == true)
			return false;
		else { // both a and b are now negative
			if (b.digits > a.digits)
				return false; // a has more digits so its less than b (because -tive)
			if (b.digits < a.digits)
				return true;
			while (cursor_b != nullptr && cursor_a != nullptr) {

				if ((int) cursor_b->data > (int) cursor_a->data)
					return false;
				if ((int) cursor_b->data < (int) cursor_a->data)
					return true;

				cursor_a = cursor_a->next;
				cursor_b = cursor_b->next;
			}
			return false;
		}
	}
}

bool operator >=(const big_number& a, const big_number& b) // PART 1
{
	return !(a < b);
}

bool operator <=(const big_number& a, const big_number& b) {
	return !(a > b);
}

bool operator==(const big_number& a, const big_number& b)
{
	return (!(a < b) && !(a > b));
}

bool operator!=(const big_number& a, const big_number& b) {
	return !(a == b);
}

ostream& operator <<(ostream& out, const big_number& n) // PART 1
{
	if (n.positive == false){//if negative
		out << "-";
	}
	node* cursor = n.head_ptr;
		while (cursor != nullptr) // go through the entire list and cout all of them one by one
		{
			out << cursor->data;
			cursor = cursor->next; // move on to the next as long as this statement holds true
		}
	return out;
}

istream& operator >>(istream& in, big_number& n) // PART 1
{
	string word;// initiate a string where you can store the input
	cin >> word;
	int base; // initiate a base
	cout << "Choose a base:";
	cin >> base; // option of choosing a base
	big_number m(word, base);
	n=m;
	return in;
}

big_number operator+(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator-(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator*(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator/(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number operator%(const big_number& a, const big_number& b)
{
	big_number answer;
	return answer;
}

big_number factorial(const big_number& a)
{
	big_number answer;
	return answer;
}
// helper functions below
void big_number :: trim() // to trim worthless "0"s before the actual value of the big number.
{
	while (head_ptr != tail_ptr && head_ptr -> data == '0'){
		head_ptr = head_ptr -> next;
		delete head_ptr -> prev;
		head_ptr -> prev = nullptr;
		--digits;
	}
}
// helper function: assume |*this| >= |m|
big_number& big_number :: sum (const big_number &m)
{
	node * cursor = tail_ptr;
	const node* mcursor = m.tail_ptr;
	digits = 0; // alert, dangerous territory.
	unsigned int dig1, dig2, result;
	unsigned int carry = 0;
	while (cursor != nullptr && mcursor != nullptr){
		dig1 = alpha.find(cursor -> data);
		dig2 = alpha.find(mcursor -> data);
		result = carry + dig1 + dig2;
		if (result >= base){
			if (base <=10)
				cursor -> data = (result % base) + '0';
			else
				cursor -> data = result + 'a' - 10;
			carry = 1;
		}
		else
		{
			if (base <=10)
				cursor -> data = result + '0';
			else
				cursor -> data = result + 'a' - 10;
			carry = 0;
		}
		cursor = cursor -> prev;
		mcursor = mcursor -> prev;
		++digits;
	}
	while (cursor != nullptr){
		dig1 = alpha.find(cursor -> data);
		result = carry + dig1;
		if (result >= base){
			if (base <=10)
				cursor -> data = (result % base) + '0';
			else
				cursor -> data = result + 'a' - 10;
			carry = 1;
		}
		else
		{
			if (base <=10)
				cursor -> data = result + '0';
			else
				cursor -> data = result + 'a' - 10;
			carry = 0;
		}
		cursor = cursor -> prev;
		++digits;
	}
	if (carry  > 0){
		head_ptr -> prev = new node;
		head_ptr -> prev -> prev = nullptr;
		head_ptr -> prev -> next = head_ptr;
		head_ptr -> prev -> data = '1';// highest that a carry can get is 1
		++digits;
		head_ptr = head_ptr -> prev;
	}
	return *this;
}
