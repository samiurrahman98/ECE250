#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  s72rahma
 * Submitted for ECE 250
 * Semester of Submission: (Fall) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

using namespace std;

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int mod(int, int) const; // personal modulus function
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
		array[i] = 0;
	}
}

/* deallocate memory for all elements instantiated using the "new" operator. */
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	delete[] this->array;
	delete[] this->array_state;
}

/* personal mod function, works with negative integer/double input. */
template<typename T >
int DoubleHashTable<T >::mod(int a, int b) const {
    if(b < 0)
    	return mod(a, -b);

    int modulus = a % b;

    if(modulus < 0)
    	modulus += b;

    return modulus;
}

/* returns the number of occupied bins in the hash table. */
template<typename T >
int DoubleHashTable<T >::size() const {
    return this->count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return this->array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
    return(this->count == 0);
}

/* h1(k) = k mod m, where m is the size of the hash table. */
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	return mod((int)obj, capacity());
}

/* h2(k) = floor(k/m) mod m, where m is the size of the hash table; adds one if the hash is even. */
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	if(h1(obj/capacity()) % 2)
		return h1(obj/capacity());
	else
		return h1(obj/capacity()) + 1;
}

/* if member is found immediately at first probe bin, return true/false depending on whether the state of the bin is empty.
   if not, loop through hash table using hash function, and incorporate the offset with every unsuccessful iteration,
   until either the object is found or the hash count exceeds the capacity of the hash table. */
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int probe = h1(obj);
	int offset = h2(obj);
	int hash_count = 0;

	if(this->array[probe] != obj) {
		while(this->array_state[probe] != EMPTY && hash_count < capacity()  && (this->array[probe] != obj || this->array_state[probe] != OCCUPIED)) {
			probe = mod((probe + offset), capacity());

			if(this->array[probe] == obj && this->array_state[probe] != EMPTY)
				return true;

			hash_count++;
		}
		return false;
	}
	else {
		if(this->array_state[probe] != EMPTY)
			return true;
		else
			return false;
	}
}

/* return value of bin at specified index. */
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	return this->array[n];
}

/* if hash table is full, throw overflow exception. if not yet full, insert function at first empty probe location
   by iterating through the available locations using the hash function; once filled, increase number of bins occupied
   count, and change bin state to occupied. */
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 if(size() >= capacity())
	 	throw overflow();
	 else {
	 	int probe = h1(obj);
	 	int offset = h2(obj);

	 	while(this->array_state[probe] == OCCUPIED) {
	 		probe = mod((probe + offset), capacity());
	 	}
	 	this->array[probe] = obj;
	 	this->array_state[probe] = OCCUPIED;
	 	this->count++;
	 }
}

/* if member is found immediately at first probe bin, return true/false depending on whether the state of the bin is empty,
   and remove the value from the bin if true. if not, loop through hash table using hash function, and incorporate the offset with every unsuccessful iteration,
   until either the object is found or the hash count exceeds the capacity of the hash table. */
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	int probe = h1(obj);
	int offset = h2(obj);
	int hash_count = 0;

	if(this->array[probe] != obj) {
		while(this->array_state[probe] != EMPTY && hash_count < capacity() && (this->array[probe] != obj || this->array_state[probe] != OCCUPIED)) {
			probe = mod((probe + offset), capacity());

			if(this->array[probe] == obj && this->array_state[probe] != EMPTY) {
				this->array_state[probe] = DELETED;
				this->array[probe] = 0;
				this->count--;
				return true;
			}
			hash_count++;
		}
		return false;
	}
	else {
		if(this->array_state[probe] != EMPTY) {
			this->array_state[probe] = DELETED;
			this->array[probe] = 0;
			this->count--;
			return true;
		}
		else
			return false;
	}
}

/* empty all bins in the hash table, and set each bin's state to EMPTY. */
template<typename T >
void DoubleHashTable<T >::clear() {
	for(int i = 0; i < this->array_size; i++) {
		this->array_state[i] = EMPTY;
		this->array[i] = 0;
	}
	this->count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
	cout << endl;
    for(int i = 0; i < capacity(); i++)
	{
		cout << i << " " << this->array[i] << " " << this->array_state[i] << endl;
	}
}

#endif