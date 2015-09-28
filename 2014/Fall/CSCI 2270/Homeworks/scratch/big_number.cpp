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
	int index = 0;
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
	while (index < s.length()){
		tail_ptr -> next = new node;
		tail_ptr -> next -> data = s[index++];
		tail_ptr -> next -> next = nullptr;
		tail_ptr -> next -> prev = tail_ptr;
		tail_ptr = tail_ptr -> next;
		++digits;
	}
}

// destructor
big_number::~big_number()//DONE (PART 1) //delete the entire doubly linked list(with the big numbers)
{
	clear_list(head_ptr, tail_ptr);
	digits = 0;
	positive = true;
}

// assignment operator
big_number& big_number::operator=(const big_number& m) // DONE (PART 1) ?
{
	if (this == &m) return *this;
	copy_list(m.head_ptr,this->head_ptr, this->tail_ptr);
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

bool operator >(const big_number& a, const big_number& b)// PART 1
{
	node * cursor_1 = a.head_ptr;
	node * cursor_2 = b.head_ptr;
	if (a.positive == true && b.positive ==false ) return true;//if a is + and b is -, obviously a is greater
	if (a.positive == false && b.positive == true ) return false;// if a is - and b is positive, a is less than b
	if (a.positive == true){//if both are positive
		if (a.digits > b.digits) return true;//we look at who has the biggest amount of digits, if a has more digits, its true
		if (a.digits < b.digits)return false;//else false
			while (cursor_1 !=nullptr && cursor_2 != nullptr){
				if ((int)cursor_1 -> data > (int)cursor_2 -> data) return true;//if the same amount of digits
				if ((int)cursor_1 -> data < (int)cursor_2 -> data) return false;
				cursor_1 = cursor_1 -> next;
				cursor_2 = cursor_2 -> next;
		}
		return false;
	}
	if (a.positive == false){//if both negative
		if (a.digits > b.digits)return false;
		if (a.digits < b.digits) return true;
			while (cursor_1 !=nullptr && cursor_2 != nullptr){
				if ((int)cursor_1 -> data > (int)cursor_2 -> data) return false;
				if ((int)cursor_1 -> data < (int)cursor_2 -> data) return true;
				cursor_1 = cursor_1 -> next;
				cursor_2 = cursor_2 -> next;
		}
		return false;
	}
}
bool operator >=(const big_number& a, const big_number& b)// PART 1
{
	if (a < b) return false;
	else return true;
}

bool operator <(const big_number& a, const big_number& b) // PART 1
{
	node * cursor_1 = a.head_ptr;
	node * cursor_2 = b.head_ptr;
	if (a.positive == true && b.positive ==false ) return false;
	if (a.positive == false && b.positive == true ) return true;
	if (a.positive == true){
		if (a.digits > b.digits) return false;
		if (a.digits < b.digits)return true;
			while (cursor_1 !=nullptr && cursor_2 != nullptr){
				if ((int)cursor_1 -> data > (int)cursor_2 -> data) return false;
				if ((int)cursor_1 -> data < (int)cursor_2 -> data) return true;
				cursor_1 = cursor_1 -> next;
				cursor_2 = cursor_2 -> next;
		}
		return false;
	}

	if (a.positive == false){
		if (a.digits > b.digits)return true;
		if (a.digits < b.digits) return false;
			while (cursor_1 !=nullptr && cursor_2 != nullptr){
				if ((int)cursor_1 -> data > (int)cursor_2 -> data) return true;//if the same amount of digits
				if ((int)cursor_1 -> data < (int)cursor_2 -> data) return false;
				cursor_1 = cursor_1 -> next;
				cursor_2 = cursor_2 -> next;
		}
		return false;
	}
}
bool operator <=(const big_number& a, const big_number& b)// PART 1
{
	if (a > b) return false;
	else return true;
}
			
bool operator==(const big_number& a, const big_number& b) // PART 1
{
	return (!(a < b) && !(a > b));

}
	
bool operator!=(const big_number& a, const big_number& b) // PART 1
{
	if (a == b) return false;
	else
		return true;
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


