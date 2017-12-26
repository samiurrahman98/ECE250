
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
 *    - n2adil
      - vskottur
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - n2adil: helped debug my count function
 	  - vskottur: helped debug my push function
 	  - b3chapma: many thanks to Ben for providing a comprehensive set of test cases
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node<Type> *left() const;
		Leftist_node<Type> *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

/* O(1): returns the element stored in this node */
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return this->element;
}

/* O(1): checks if the heap is empty */
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return (this == nullptr);
}

/* O(1): returns the address of the left subtree */
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	return this->left_tree;
}

/* O(1): returns the address of the right subtree */
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	return this->right_tree;
}

/* O(n): returns the number of instances of the argument in the heap */
template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const {
	if(this == nullptr)
		return 0;

    if(this->element == obj)
       return 1 + left()->count(obj) + right()->count(obj);
    else
    	return left()->count(obj) + right()->count(obj);
}

/* O(1): returns the null-path-length of the root node */
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	return this->heap_null_path_length;
}

/* O(log(n)): inserts new node into the heap */
template <typename Type>
void Leftist_node<Type>::push(Leftist_node *n, Leftist_node *&obj) {
	/* if the new heap is null, return */
	if(n == nullptr)
		return;

	/* Case I: insert the new heap into this heap; since it's null, set the pointer to this to be the new heap and return */
	if(obj == nullptr) {
		obj = n;
		return;
	}

	/* Case II: If the current node is storing a value less-than-or-equal-to the value stored in the root of the new heap, push the new node onto the right sub-tree */
	if(obj->element <= n->element) {
		int left_null_path = -1;

		push(n, obj->right_tree);

		if(obj->left_tree != nullptr)
			left_null_path = obj->left()->heap_null_path_length;

		/* update the null path length by adding 1 to the minimum between the left and right null-path lengths of the root node */
		if(left_null_path > -1)
			obj->heap_null_path_length = std::min(obj->right()->heap_null_path_length, left_null_path) + 1;

		/* if the left sub-tree has a shorter null-path-length than the right sub-tree, swap*/
		if(left_null_path < obj->right()->heap_null_path_length)
			std::swap(obj->right_tree, obj->left_tree);
	}
	/* Case III: Set the pointer to this to be the new heap and push this node into the new heap */
	else {
		Leftist_node* temp = obj;
		obj = n;
		push(temp, obj);
		return;
	}
}

/* O(n): called by the destructor to clear the heap */
template <typename Type>
void Leftist_node<Type>::clear() {
	if (this != nullptr) {
		left()->clear();
		right()->clear();

		delete(this);
		return;
	}
	else
		return;
}

#endif