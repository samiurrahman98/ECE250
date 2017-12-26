#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/*****************************************
 * UW User ID:  ctwinqui
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2013
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>
using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count; //Number of elements in hash table
		int power;
		int array_size; //Size of hash table
		T *array;
		state *occupied;

		
		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function
		

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
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
occupied( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
		array[i] = 0;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	//Handle memory deletion
	delete [] array;
	delete [] occupied;
}

template<typename T >
int DoubleHashTable<T >::size() const { 
	return count; //returns number of elements in hash table
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size; //returns the size of hash (the array size)
}

template<typename T >
double DoubleHashTable<T >::load_factor() const {
	return (double)(count)/(double)(array_size); 
	//Returns how full the hash table is.
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	return count == 0; //Returns true when count is 0, else false
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	return ((int)obj) % array_size;
	//Cast the value being passed in  to an integer, then find i mod M
	//Where i = obj and M = array_size
	//This is the first hash
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	//The second hash uses the first hash, but the value is obj/array_size.
	//as an argument rather then obj, so call h1 with a different argument.
	if(h1(obj/array_size) % 2 == 0)
	{
		//If the hash is even, return an odd jump (add 1)
		return h1(obj/array_size) + 1;
	}
	return h1(obj/array_size);
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	//This function tests if a certain value is in the hash table
	int numberOfHashes = 1;
	int testBin = h1(obj); //set the first bin to test as the original hash.

	//While the hash bins are occupied, there could still be the value
	//that had been pushed donw the hash. So, while we havent found the
	//value in the table and the table is occupied, keep searching through
	//the hash table
	while(occupied[testBin] != EMPTY && numberOfHashes != array_size  &&
		(array[testBin] != obj || occupied[testBin] != OCCUPIED))
	{
		//Make sure we dont exceed the hash table size.
		testBin += h2(obj);
		testBin = testBin % array_size;
		
	}
	//Once we have exited if we found the obj, return true, else return false
	if(array[testBin] == obj && occupied[testBin] == OCCUPIED)
	{
		return true;
	}
	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	//If n is outside the Hash table bounds, throw exception
	if(n < 0 || n >= array_size)       
	{
		throw ArrayBoundsException();
	}
	//Else, return the value in bin n
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	//If our hash table is full, throw an overflow
	if(count >= array_size)
	{
		throw overflow();
	}
	//Keep hashing until we find an empty spot to place obj
	int testBin = h1(obj);
	while(occupied[testBin] == OCCUPIED)
	{
		testBin += h2(obj);
		testBin = testBin % array_size;
	}
	//Once we find it, set bin to obj, increment count and set occupied
	array[testBin] = obj;
	occupied[testBin] = OCCUPIED;
	count ++;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	//We use number of hashes to check if we have gone through the entire 
	//hash table and haven't found obj
	int numberOfHashes = 1;
	int testBin = h1(obj);

	//Stop looking for a value if
	//1: we find an empty bin, if the value was in the hash, 
	//it would have been here, so return false
	//
	//2: If the bin is occupied an has obj in it, return true,
	//and set testBin to delete, decrement count
	//
	//3: If the have hashed through every spot in the array,
	//This is an edge case where there are no empty bins, so
	//return that the value has not been found
	while(occupied[testBin] != EMPTY && numberOfHashes != array_size 
		&& (array[testBin] != obj || occupied[testBin] != OCCUPIED))
	{
		testBin += h2(obj);
		testBin = testBin % array_size;
		numberOfHashes ++;
	}
	//If we found the value return true, else return false
	if(array[testBin] == obj && occupied[testBin] == OCCUPIED)
	{
		array[testBin] = -1;
		occupied[testBin] = DELETED;
		count--;
		return true;
	}
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	//Clear the table, reset occupied and reset count
	 for(int x = 0; x < array_size; x++)
	 {
		 array[x] = 0;
		 occupied[x] = EMPTY;
	 }
	 count = 0;
}

template<typename T >
void DoubleHashTable<T >::print() const {
	//Print out the hash table
	cout << "Hash Table value:    Occupied Status" << endl;
    for(int x = 0; x < array_size; x++)
	{
		cout << array[x] << "       " << occupied[x] << endl;
	}
	return;
}

#endif