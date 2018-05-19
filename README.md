# University of Waterloo - ECE250 (Fall 2017) Lab Projects
All projects are written in C++. Project descriptions are provided in each Lab folder. Test files have been provided, both by the course co-ordinator, as well as my colleague, Ben.

## Lab Project 1 - Dynamic Stack
The goal of this project is to design and implement a dynamic stack data structure. A
stack is a data structure that stores elements in an ordered list and allows insertions and
deletions at one end only (the top of stack) in O(1) time. A dynamic stack is able to
increase its size if necessary in O(n).

## Lab Project 2 - Open Addressing - Double Hashing
In this project, you design and implement a hash table data structure. A hash table is a data
structure where values are mapped to a position in a table using a hash function. For this
project, you will implement a double hash table in which collisions are resolved using double
hashing. We will use hash functions sufficiently even so as to allow all expected constant-time
operations to be O(1).

## Lab Project 3 - Leftist Heap
A mergeable heap is an ADT that stores an element from an ordered set, and supports the
operations Insert, Min, and Extract-Min (just like Min Priority Queues). Mergeable heaps
support an additional operation named “Merging Two Heaps”. Two implementations of the
mergeable heap are the leftist tree and the binomial heap. We implement leftist heap in this
project. Essentially, a leftist heap is very similar to an AVL tree but rather than height it uses the
null-path length of a node; that is, the minimum path length from the node to a descendent that is
not a full node. The name leftist comes from the fact that, in leftist heap, the left subtree of each
node is usually taller than the right subtree. You can visually see the steps involved in each
operation of leftist heap on the course website.

## Lab Project 4 - Minimum Spanning Tree (MST) using Kruskal's Algorithm
In this project, you implement the Minimum Spanning Tree (MST) of a weighted undirected graph, using
the Kruskal’s algorithm. We consider the nodes in the graph to be numbered from 0 to n – 1. This means
a graph with 4 nodes, has nodes named 0, 1, 2 and 3. Each edge has a weight (a positive number of double
type) associated with it. You will be implementing the Kruskal’s algorithm using Disjoint sets, a wellknown
data structure for grouping n elements (nodes) into a collection of disjoint sets (connected
components).
