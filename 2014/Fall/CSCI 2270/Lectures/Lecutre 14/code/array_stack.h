#include <iostream>
#include "dynamic_size_array_unsorted.h"

struct array_stack {
	int_array arr;
};

void init(array_stack& stk);

void destr(array_stack& stk);

void push(array_stack& stk, const int& payload);

bool pop(array_stack& stk);

int top(const array_stack& stk);

bool empty(const array_stack& stk);

void print(const array_stack& stk);

