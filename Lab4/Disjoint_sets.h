
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?

struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next; // ptr to next node

	ll_entry(int val) {
		this->content = val;
		this->ptr_to_info = nullptr;
		this->next = nullptr;
	}
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;

	set_info(ll_entry* h, ll_entry* t, int s) {
		this->head = h;
		this->tail = t;
		this->size = s;
	}
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
	void make_set(int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
}

Disjoint_set::~Disjoint_set() {
	for(int i = 0; i < this->initial_num_sets; i++) {
		if(this->nodes[i] != nullptr)
			delete this->nodes[i];

		if(this->sets[i] != nullptr)
			delete this->sets[i];
	}
	delete[] this->nodes;
	delete[] this->sets;
}
int Disjoint_set::find_set(int item) const {
	return this->nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return this->set_counter;
}

void Disjoint_set::union_sets(int node_1, int node_2) {
	if(node_1 != node_2) {
		/* si1 = larger set, si1 = smaller set */
		set_info* si1 = this->nodes[node_1]->ptr_to_info;
		set_info* si2 = this->nodes[node_2]->ptr_to_info;

		// ni1: the index of the larger set, ni2: the index of the smaller set
		int ni1 = si1->size >= si2->size ? node_1 : node_2; 
		int ni2 = si1->size < si2->size ? node_1 : node_2;

		si1 = this->nodes[ni1]->ptr_to_info;
		si2 = this->nodes[ni2]->ptr_to_info;
		ll_entry* current = si2->head;

		/* iterate through the shorter list and modify the pointers */
		while (current != nullptr) {
			current->ptr_to_info = si1;
			current = current->next;
		}

		ll_entry* old_tail = si1->tail;
		old_tail->next = si2->head;

		si1->tail = si2->tail;
		si1->size += si2->size;

		this->set_counter--;
	}
}

/* creates linked list to hold the disjoint sets */
void Disjoint_set::make_set(int index) {
	ll_entry* node = new ll_entry(index);
	nodes[index] = node;
	set_info* info = new set_info(node, node, 1);
	sets[index] = info;
	node->ptr_to_info = info;
}

#endif