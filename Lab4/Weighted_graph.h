
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID: s72rahma@uwaterloo.ca
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
 *    - n2adil (for having the patience to explain how structs work because
 		I skipped all of my 150 lectures after midterms because I didn't like
 		Paul Ward)
 	  - svkottur (moral support for pointers because I HATE POINTERS)
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    - b3chapma (thank you once again to ben for his wonderful test cases)
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

struct Edge;
struct Edge_List;
struct Adjacency_Vertex;
struct Adjacency_List;

struct Edge {
	Edge* previous;
	Edge* next;
	int v1;
	int v2;
	double weight;
	
	Edge(int v1, int v2, double w) {
		this->previous = nullptr;
		this->next = nullptr;
		this->v1 = v1;
		this->v2 = v2;
		this->weight = w;
	}
};

struct Edge_List {
	Edge* head;
	Edge* tail;
	int count;

	Edge_List() {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
};

struct Adjacency_Vertex {
	Edge* edge;
	Adjacency_Vertex* previous;
	Adjacency_Vertex* next;
	int val;

	Adjacency_Vertex(Edge* e, int v) {
		this->previous = nullptr;
		this->next = nullptr;
		this->edge = e;
		this->val = v;
	}
};

struct Adjacency_List {
	Adjacency_Vertex* head;
	Adjacency_Vertex* tail;
	int count;

	Adjacency_List() {
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
};

class Weighted_graph {
	private:
		static const double INF;
		Adjacency_List** adj_list;
		int num_nodes;
		Edge_List* edge_list;

		/* Do not implement these functions! By making these private and not implementing them, any attempt to make copies or assignments will result in errors */
		Weighted_graph(Weighted_graph const &);
		Weighted_graph &operator=(Weighted_graph);

		// your choice
		void insert_vertex(Adjacency_List*&, Edge*, int);
		void remove_vertex(Adjacency_List*&, Adjacency_Vertex*&);
		Adjacency_Vertex* find_vertex(Adjacency_List*, int);
		void insert_edge_private(Edge*&);
		void remove_edge(Edge*&);

	public:
		Weighted_graph(int = 10);
		~Weighted_graph();

		int degree(int) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge(int, int, double);
		bool erase_edge(int, int);
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n) : adj_list(new Adjacency_List*[n]),
num_nodes(n),
edge_list(new Edge_List()) {
	for(int i = 0; i < n; i++)
		this->adj_list[i] = new Adjacency_List();
}

Weighted_graph::~Weighted_graph() {
	clear_edges();

	for(int i = 0; i < this->num_nodes; i++)
		delete this->adj_list[i];

	delete[] this->adj_list;
	delete this->edge_list;
}

void Weighted_graph::insert_vertex(Adjacency_List* &list, Edge* edge, int value) {
	Adjacency_Vertex* new_vertex = new Adjacency_Vertex(edge, value);

	if(list->head != nullptr) {
		Adjacency_Vertex* old_tail = list->tail;
		new_vertex->previous = old_tail;
		old_tail->next = new_vertex;
	}
	else
		list->head = new_vertex;

	list->tail = new_vertex;
	list->count++;
}

void Weighted_graph::remove_vertex(Adjacency_List* &list, Adjacency_Vertex* &vertex) {
	Adjacency_Vertex* previous_vertex = vertex->previous;
	Adjacency_Vertex* next_vertex = vertex->next;

	if(previous_vertex == nullptr && next_vertex != nullptr) {
		next_vertex->previous = nullptr;
		list->head = next_vertex;
	}
	else if(previous_vertex != nullptr && next_vertex == nullptr) {
		previous_vertex->next = nullptr;
		list->tail = previous_vertex;
	}
	else if(previous_vertex != nullptr && previous_vertex != nullptr) {
		previous_vertex->next = next_vertex;
		next_vertex->previous = previous_vertex;
	}

	delete vertex;
	list->count--;
}

Adjacency_Vertex* Weighted_graph::find_vertex(Adjacency_List* list, int value) {
	Adjacency_Vertex* vertex = list->head;

	while(vertex != nullptr) {
		if(vertex->val == value)
			return vertex;

		vertex = vertex->next;
	}
	return nullptr;
}

void Weighted_graph::insert_edge_private(Edge* &new_edge) {
	Edge* current_edge = this->edge_list->head;

	if(current_edge == nullptr)
		this->edge_list->head = new_edge;
	else {
		if(new_edge->weight <= current_edge->weight) {
			this->edge_list->head = new_edge;
			new_edge->next = current_edge;
			current_edge->previous = new_edge;

			if(current_edge->next == nullptr)
				this->edge_list->tail = current_edge;
		}
		else {
			while(new_edge->weight >= current_edge->weight && current_edge->next != nullptr)
				current_edge = current_edge->next;

			if(new_edge->weight <= current_edge->weight) {
				current_edge->previous->next = new_edge;
				new_edge->previous = current_edge->previous;
				current_edge->previous = new_edge;
				new_edge->next = current_edge;
			}
			else {
				current_edge->next = new_edge;
				new_edge->previous = current_edge;
				this->edge_list->tail = new_edge;
			}
		}
	}
}

void Weighted_graph::remove_edge(Edge* &edge) {
	Edge* previous_edge = edge->previous;
	Edge* next_edge = edge->next;

	if(previous_edge == nullptr && next_edge != nullptr) {
		next_edge->previous = nullptr;
		edge_list->head = next_edge;
	}
	else if(previous_edge != nullptr && next_edge == nullptr) {
		previous_edge->next = nullptr;
		edge_list->tail = previous_edge;
	}
	else if(previous_edge != nullptr && next_edge != nullptr) {
		previous_edge->next = next_edge;
		next_edge->previous = previous_edge;
	}

	delete edge;
	edge_list->count--;
}

int Weighted_graph::degree(int u) const {
	if(u < 0 || u > (this->num_nodes - 1))
		throw illegal_argument();
	else
		return this->adj_list[u]->count;
}

int Weighted_graph::edge_count() const {
	return this->edge_list->count;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	int visited = 0;
	double sum = 0.0;

	Disjoint_set* disjoint_set = new Disjoint_set(this->num_nodes);

	for(int i = 0; i < num_nodes; i++)
		disjoint_set->make_set(i);

	Edge* current_edge = this->edge_list->head;

	while(current_edge != nullptr && disjoint_set->num_sets() > 1) {
		if(disjoint_set->find_set(current_edge->v1) != disjoint_set->find_set(current_edge->v2)) {
			disjoint_set->union_sets(current_edge->v1, current_edge->v2);
			sum += current_edge->weight;
		}

		visited++;
		current_edge = current_edge->next;
	}

	delete disjoint_set;
	return std::pair<double, int>(sum, visited);
}

bool Weighted_graph::insert_edge(int i, int j, double d) {
	if((i < 0 || i > (num_nodes - 1)) || (j < 0 || j > (num_nodes - 1)) || d <= 0)
		throw illegal_argument();
	else if(i == j)
		return false;
	else {
		Adjacency_List* list_1 = this->adj_list[i];
		Adjacency_List* list_2 = this->adj_list[j];

		Adjacency_Vertex* v1 = find_vertex(list_1, j);
		Adjacency_Vertex* v2 = find_vertex(list_1, j);

		if(v1 != nullptr && v2 != nullptr) {
			remove_edge(v1->edge);
			Edge* new_edge = new Edge(i, j, d);
			insert_edge_private(new_edge);

			this->edge_list->count++;
			v1->edge = new_edge;
			v2->edge = new_edge;
		}
		else {
			Edge* new_edge = new Edge(i, j, d);
			insert_edge_private(new_edge);
			this->edge_list->count++;
			insert_vertex(list_1, new_edge, j);
			insert_vertex(list_2, new_edge, i);
		}
		return true;
	}
}

bool Weighted_graph::erase_edge(int i, int j) {
	if((i < 0 || i > (num_nodes - 1)) || (j < 0 || j > (num_nodes - 1)))
		throw illegal_argument();
	else if(i == j)
		return true;
	else {
		Adjacency_List* list_1 = this->adj_list[i];
		Adjacency_List* list_2 = this->adj_list[j];

		Adjacency_Vertex* v1 = find_vertex(list_1, j);
		Adjacency_Vertex* v2 = find_vertex(list_2, i);

		if(v1 == nullptr || v2 == nullptr)
			return false;
		else {
			remove_edge(v1->edge);
			remove_vertex(list_1, v1);
			remove_vertex(list_2, v2);
			return true;
		}
	}
}

void Weighted_graph::clear_edges() {
	for(int i = 0; i < this->num_nodes; i++) {
		Adjacency_List* list = this->adj_list[i];
		Adjacency_Vertex* vertex = list->head;

		while(vertex != nullptr) {
			if(vertex->next == nullptr) {
				delete vertex;
				vertex = nullptr;
			}
			else {
				vertex = vertex->next;
				delete vertex->previous;
			}
		}

		list->head = nullptr;
		list->tail = nullptr;
		list->count = 0;
	}

	Edge* current_edge = this->edge_list->head;

	while(current_edge != nullptr) {

		if(current_edge->next == nullptr) {
			delete current_edge;
			current_edge = nullptr;
		}
		else {
			current_edge = current_edge->next;
			delete current_edge->previous;
		}
	}

	this->edge_list->head = nullptr;
	this->edge_list->tail = nullptr;
	this->edge_list->count = 0;
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif