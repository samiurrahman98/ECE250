
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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}


template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

/* O(1): checks if the heap is empty */
template <typename Type>
bool Leftist_heap<Type>::empty() const {
	return (this->root_node == nullptr);
}

/* O(1): returns the number of nodes in the heap */
template <typename Type>
int Leftist_heap<Type>::size() const {
	return this->heap_size;
}

/* O(1): returns the null-path-length of the root node */
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
	if (this->root_node == nullptr) {
		return -1;
	}
	return this->root_node->null_path_length();
}

/* O(1): Returns the element at the top of the heap. If the tree is empty, throw an underflow exception */
template <typename Type>
Type Leftist_heap<Type>::top() const {
	if(this->root_node != nullptr)
		return this->root_node->retrieve();
	else
		throw underflow();
}

/* O(n): returns the number of instances of the argument in the heap */
template <typename Type>
int Leftist_heap<Type>::count(Type const &obj) const {
	if (this->root_node == nullptr)
		return 0;
	else
		return this->root_node->count(obj);
}

/* O(log(n)) */
template <typename Type>
void Leftist_heap<Type>::push(Type const &obj) {
	Leftist_node<Type> * new_node = new Leftist_node<Type>(obj);

	if(this->root_node == nullptr)
		this->root_node = new_node;
	else
		this->root_node->push(new_node, this->root_node);
	
	this->heap_size++;
	new_node = nullptr;
}

/* O(log(n)): delete the root node and return its value */
template <typename Type>
Type Leftist_heap<Type>::pop() {
	/* If the tree is empty, throw an underflow exception*/
	if(empty())
		throw underflow();

	/* Make the left sub-tree of the root node the new root node, and the push the right sub-tree of the original root node onto the new root node */
	Type temp = this->root_node->retrieve();
	Leftist_node<Type> * original = this->root_node;
	this->root_node = this->root_node->left();
	this->root_node->push(original->right(), this->root_node);

	this->heap_size--;
	
	delete original;
	return temp;
}

/* O(n): called by the destructor to clear the heap */
template <typename Type>
void Leftist_heap<Type>::clear() {
	this->root_node->clear();
	this->root_node = nullptr;
	this->heap_size = 0;
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif