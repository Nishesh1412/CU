//============================================================================
// Name        : big_number.cpp
// Author      : Nishesh Shukla
// Version     : 3.0
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
		cursor = cursor->next)
	{
		if (isdigit(cursor->data))
			digit = cursor->data - '0';
		else
			digit = cursor->data - 'a' + 10;
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
}

// assignment operator
big_number& big_number::operator=(const big_number& m) // DONE (PART 1)
{
	if (this == &m) return *this;
	base = m.base;
	copy_list(m.head_ptr,this->head_ptr, this->tail_ptr);
	positive = m.positive;
	digits = m.digits;
	return *this;
}

// set value to original value + b; return answer in original number's base
big_number& big_number::operator+= (const big_number& b)//DONE PART 2
{
	trim ();
	big_number n1(*this);
	big_number n2(b);
	n2.trim();
	n1.positive = true;
	n2.positive = true;
	if (n1 < n2)
	{
		std:: swap(n1, n2);
		n1.positive = b. positive;
	}
	else {
		n1.positive = positive;
	}
	if (positive != b.positive){
		n1.diff(n2);
	}
	else {
		n1.sum(n2);
	}
	*this = n1;
	trim();
	return *this;
}

// set value to original value * b; return answer in original number's base
big_number& big_number::operator*= (const big_number& b)//DONE PART 2
{
	big_number n1 = mult(b);
	positive = (b.positive == positive);
	*this = n1;
	return *this;
}

// set value to original value - b; return answer in original number's base
big_number& big_number::operator-= (const big_number& b)
{
	big_number n1(b);
	n1.positive = !n1.positive;
	*this += n1;
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
	big_number temp('1');
	*this += temp;
	return *this;
}

// prefix decrement
big_number& big_number::operator--()
{
	big_number temp('1');
	*this -= temp;
	return *this;
}

bool operator >(const big_number& a, const big_number& b) {
	node * cursor_a = a.head_ptr;
	node * cursor_b = b.head_ptr;

	if (a.positive == true) {
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
		if (b.positive == true)
			return false;
		else { // both a and b are now negative
			if (a.digits > b.digits)
				return false; // a has more digits so its less than b (because -tive)
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
		while (cursor != nullptr)
		{
			out << cursor->data;
			cursor = cursor->next;
		}
	return out;
}

istream& operator >>(istream& in, big_number& n) // PART 1
{
	string word;
	cin >> word;
	int base;
	cout << "Choose a base:";
	cin >> base;
	big_number m(word, base);
	n=m;
	return in;
}

big_number operator+(const big_number& a, const big_number& b)//DONE PART 2
{
	big_number answer;
	answer += a;
	answer += b;
	return answer;
}

big_number operator-(const big_number& a, const big_number& b)
{
	big_number answer;
	answer -= a;
	answer -= b;
	return answer;
}

big_number operator*(const big_number& a, const big_number& b)
{
	big_number answer;
	answer *= a;
	answer *= b;
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
	node* cursor = tail_ptr;
		const node* mcursor = m.tail_ptr;
		digits = 0;  // a little scary, but let's roll with it anyway
		unsigned int dig1, dig2, result;
		unsigned int carry = 0;
		while (cursor != nullptr && mcursor != nullptr)
		{
			// we added an alphabet string to the big_number.h
			dig1 = alpha.find(cursor->data);
			dig2 = alpha.find(mcursor->data);
			result = carry + dig1 + dig2;
			if (result >= base) // we have to carry
			{
				// this code is simpler, more correct and more elegant;
				// thanks to Audi Li!
				cursor->data = alpha[result % base];
				carry = 1;
			}
			else // we don't have to carry
			{
				cursor->data = alpha[result];
				carry = 0;
			}
			cursor = cursor->prev;
			mcursor = mcursor->prev;
			++digits;
		}
		while (cursor != nullptr)
		{
			dig1 = alpha.find(cursor->data);
			result = carry + dig1;
			if (result >= base) // carry
			{
				cursor->data = alpha[result % base];
				carry = 1;
			}
			else // no carry
			{
				cursor->data = alpha[result];
				carry = 0;
			}
			cursor = cursor->prev;
			++digits;
		}

		if (carry > 0)
		{
			head_ptr->prev = new node;
			head_ptr->prev->prev = nullptr;
			head_ptr->prev->next = head_ptr;
			head_ptr->prev->data = '1';
			++digits;
			head_ptr = head_ptr->prev;
		}
		return *this;

}

// friend for comparing digits
int cmp(const big_number& a, const big_number& b)
{
	if (a.digits > b.digits) return 1;
	if (a.digits < b.digits) return -1;
	const node* a_cursor;
	const node* b_cursor;
	for (a_cursor = a.head_ptr, b_cursor = b.head_ptr;
		b_cursor != nullptr && a_cursor->data == b_cursor->data;
		b_cursor = b_cursor->next, a_cursor = a_cursor->next)
		;
	if (a_cursor == nullptr) return 0;
	if (a_cursor->data > b_cursor->data) return 1;
	return -1;
}

big_number big_number :: mult(const big_number& b) const {
	big_number n1(*this);
	big_number n2(b);
	big_number result;
	big_number intermediate;
	node* cursor;
	node* b_cursor = n2.tail_ptr;
	node* i_cursor;
	int val1, val2, carry;
	int basePower = 1;
	int i;
	carry = 0;
	while(b_cursor)
	{
		val2= alpha.find(b_cursor->data);
		cursor = n1.tail_ptr;
		intermediate = big_number();
		for(i = 1;i < basePower; ++i)
		{
			intermediate.head_ptr->prev = new node;
			intermediate.head_ptr->prev->data = '0';
			intermediate.head_ptr->prev->next = intermediate.head_ptr;
			intermediate.head_ptr->prev->prev = nullptr;
			intermediate.head_ptr = intermediate.head_ptr->prev;
			++intermediate.digits;
		}
		i_cursor = intermediate.head_ptr;
		while(cursor)
		{
			if(!i_cursor)
			{
				i_cursor = new node;
				i_cursor->prev = nullptr;
				i_cursor->next = intermediate.head_ptr;
				intermediate.head_ptr->prev = i_cursor;
				intermediate.head_ptr = i_cursor;
				++intermediate.digits;
			}
			val1 = alpha.find(cursor->data);
			val1 = val1*val2 + carry;
			i_cursor->data = alpha[val1 % base];
			carry= val1/base;
			cursor = cursor->prev;
			i_cursor = i_cursor->prev;
		}
		result += intermediate;
		b_cursor = b_cursor->prev;
		++basePower;
	}
	if (carry)
	{
		result.head_ptr -> prev = new node;
		result.head_ptr -> prev -> next = result.head_ptr;
		result.head_ptr -> prev -> data = alpha[carry];
		result.head_ptr = result.head_ptr -> prev;
	}
	result.positive =(positive ==b.positive);
	return result;

}

big_number& big_number:: diff (const big_number& m){
	node* cursor = tail_ptr;
	node* m_cursor = m.tail_ptr;
	int val1,val2,borrow;
	borrow = 0;
	while ( m_cursor)
	{
		val1 = alpha.find(cursor->data);
		val2 = alpha.find(m_cursor->data);
		val1 -= val2 + borrow;
		if(val1<0)
		{
			val1+=base;
			borrow = 1;
		}
		else{
			borrow=0;
		}
		//cursor->data = val1 + '0';
		cursor->data = alpha[val1];
		cursor = cursor->prev;
		m_cursor = m_cursor->prev;
	}
	while(cursor)
	{
		val1 = alpha.find(cursor->data);
		val1-=borrow;
		if(val1<0)
		{
			val1 += base;
			borrow=1;
		}
		else{
			borrow=0;
		}
		//cursor->data = val1 + '0';
		cursor->data = alpha[val1];
		cursor = cursor->prev;
	}
	if(borrow)
	{
		node* temp = head_ptr;
		head_ptr->next->prev = nullptr;
		head_ptr= head_ptr->next;
		delete temp;
	}
	return *this;
}
