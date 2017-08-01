/*
 * ==========================Graph.h===========================
 * By: Zhu Jing Wang
 * header file for Graph class
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "hashfunc.h"
#include "HashTable.h"
using namespace std;

struct edge{
	string s;
	string c;
};
struct adj{
	string name;
	vector<edge> e;
	bool visited;
};
struct paths{
	int length;
	string path;
};

class Graph{
public:
	//constructor
	Graph();
	//destructor
	~Graph();

	//print out the adjacency list
	void print();
	//unmark all vertices as unvisited
	void unmarkAll();
	//find a vertex in the adjacency list, returns its location
	int find(string n);
	//find all paths from a source vertex to a dastination vertex
	void Find_All_Paths(string s, string d);
	//creats adjacency list
	void create_ajlist(vector<string> &n, HashTable &r, HashTable &t);
	//print out all paths from a source vertex to a destination vertex
	void printpath();
	//print out the shortest path
	void print_shortest_path();
	//find the shortest path, returns its location
	int find_min();

private:
	static const int TSIZE = 1024;
	static const int INITIAL_CAPACITY= 10;

	//adjacency list
	adj  *ajlist;
	//store unfinished paths during recursion
	string *path;
	//store finished paths
	vector<paths> all_paths;

	//helper function to find all paths
	void Find_All_Paths_Until(string u, string d,int &path_index, string e);
	//helper function to creat adjacency list
	void create_ajlist_helper(int index, vector<string> c, HashTable &r);
	string build_edge(int index, int i);
	paths build_paths(int count, string a);
	void expand();
	void expand_path();
	int used;
	int capacity;
	int path_used;
	int path_capacity;
};
#endif
