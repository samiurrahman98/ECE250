/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  s72rahma@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission: Fall 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10); 
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
/* default value of 10 - if passed parameter < 1, use an array size of 1 */
array_size( (n < 1) ? 1: n ),
initial_size((n < 1) ? 1: n)
{
	array = new int[array_size];
}

/* De-allocate the memory that was previously reserved for the stack array and reset all variables to 0 */
Dynamic_stack::~Dynamic_stack() {
	delete[] this->array;
	this->count = 0;
	this->array_size = 0;
	this->initial_size = 0;
}

/* Return the integer at the top of the stack in O(1); may throw an underflow exception */
int Dynamic_stack::top() const {
	if(empty())
		throw underflow();
	else {
		int t = size() - 1; // index of top element
		return this->array[t];
	}
}

/* return the number of elements currently stored in the stack in O(1) */
int Dynamic_stack::size() const {
	return this->count;
}

/* return true if stack is empty false otherwise in O(1) */
bool Dynamic_stack::empty() const {
	return size() == 0;
}

/* return the capacity of stack in O(1) */
int Dynamic_stack::capacity() const {
	return this->array_size;
}


void Dynamic_stack::push( int const &obj ) {
	/* If the stack is full, create a new array with an array size of 2n (n = current size of array),
	and copy over the elements of original array to new array; O(n) due to iterative copy. Once the 
	copying process is complete, deallocate the memory for the original array as it is no longer needed,
	and change the address the pointer is pointing to, to the new array - make sure to update the stack capacity
	by multiplying the previous capacity by 2. Finally, push. */
	if(size() == capacity()) {
		int *double_array;
		double_array = new int[2*capacity()];
		int t = size() - 1; // index of top element
		for(int i = 0; i <= t; i++) {
			*(double_array + i) = *(this->array + i); // 
		}

		delete[] this->array;
		this->array = double_array;

		this->array_size *= 2;

		++t;
		this->array[t] = obj;
		this->count++;

		double_array = NULL;
		delete[] double_array;
	}
	else {
		int t = size() - 1; // index of top element
		++t;
		this->array[t] = obj;
		this->count++;
	}
}

/* Remove the element at the top of the stack (and return it as well), in constant time O(1). If the stack is empty, throw an underflow exception. */
int Dynamic_stack::pop() {
	if(empty())
		throw underflow();
	else {
		int t = size() - 1; // index of top element
		int pop = this->array[t];
		this->array[t] = 0;
		this->count = t;
		return pop;
	}
}

/* Remove all the elements from the stack. If the current size of the stack is not equal to the initial size of the stack, delete the current stack
and create a new stack with the initial size of the stack (while resetting the variables the associated variables with the appropriate values. */
void Dynamic_stack::clear() {

	if(capacity() != this->initial_size) {
		delete[] this->array;
		this->array = new int[this->initial_size];
		this->count = 0;
		this->array_size = this->initial_size;
	}
	else {
		this->count = 0;
	}
}
#endif