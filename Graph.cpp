/*
 * ======================Graph.cpp=============================
 * By:Zhu Jing Wang
 * Purpose:
 * The implementation of Graph. I'm using an adjacency list to represent the
 * graph. I'm also using DFS to find paths among vertices.This implementation
 * allows the client to find all paths between any given vertices and the
 * shortest path between any given two vertices
 */
#include <iostream>
#include <vector>
#include <string>

#include "hashfunc.h"
#include "Graph.h"
#include "HashTable.h"

using namespace std;
/*
 * Graph()
 * constructor
 */
Graph::Graph()
{
	ajlist = new adj[INITIAL_CAPACITY];
	used = 0;
	capacity = INITIAL_CAPACITY;
	path = new string[INITIAL_CAPACITY];
	path_used = 0;
	path_capacity = INITIAL_CAPACITY;

}

/*
 * ~Graph()
 * destructor
 */
Graph::~Graph()
{
	delete[] ajlist;
	delete[] path;
}

/*
 * create_ajlist(vector<string> &n, HashTable &r, HashTable &t)
 * call a helper function to create the adjacency list
 */
void Graph::create_ajlist(vector<string> &n, HashTable &r, HashTable &t)
{
	int nsize = (int)n.size();

	for(int i = 0; i<nsize; i++){
		if(used ==capacity){
			expand();
		}
		string ta = n[i];
		ajlist[i].name = ta;
		used++;

		if(t.get(ta).empty()){
			ajlist[i].e = vector<edge>();
		}
		else
			create_ajlist_helper(i, t.get(ta), r);
	}
}

/*
 * create_ajlist_helper(int index,vector<string> c,HashTable &r)
 * create the adjacency list
 */
void Graph::create_ajlist_helper(int index,vector<string> c,HashTable &r)
{
	int csize = (int)c.size();
	for(int i = 0; i <csize; i++){
		if(r.get(c[i]).empty())
			return;
		int vsize = (int)r.get(c[i]).size();
		for (int j = 0; j<vsize; j++){
			edge temp;
			temp.s = r.get(c[i])[j];
			temp.c = c[i];
			ajlist[index].e.push_back(temp);
		}
	}
}

/*
 * print()
 * print out the adjacency list(I wrote this function just to check if my
 * adjacency list works)
 */
void Graph::print()
{
	for(int i = 0; i< used; i++){
		cout<<i<<": "<<ajlist[i].name<<endl;
		int vecsize = (int)ajlist[i].e.size();
		for (int j=0; j<vecsize; j++){
			cout<<"("<<ajlist[i].e[j].s<<" "<<ajlist[i].e[j].c<<") ";
		}
		cout<<endl;
	}
}

/*
 * unmarkAll()
 * make all vertices in the graph as unvisited
 */
void Graph::unmarkAll()
{
	for(int i = 0; i < used; ++i){
		ajlist[i].visited = false;
	}
}

/*
 * Find_All_Paths(string s, string d)
 * call helper function to find all possible paths between two vertices
 */
void Graph::Find_All_Paths(string s, string d)
{
	unmarkAll();
	int path_index = path_used;
	Find_All_Paths_Until(s,d,path_index,"");
}

/*
 * Find_All_Paths_Until(string u, string d, int &path_index, string e)
 * DFS to find all possible paths between two vertices
 */
void Graph::Find_All_Paths_Until(string s, string d, int &path_index, string e)
{
	ajlist[find(s)].visited = true;//mark the vertex as visited
	if(path_used == path_capacity)
		expand_path();
	if(path_used==0)//put the source vertex to the path
		path[path_index]=s;
	else if(path_used!=0)//put part of the path to the path
		path[path_index]=e;
	path_index++;
	path_used++;
	if(s == d and path_index > 1){//base case, if we find our destination
		string a;             //vertex, we backtrace
		int count = 0;
		for(int i=0; i<path_index; i++){
			a=a+path[i];
			count++;
		}
		all_paths.push_back(build_paths(count,a));//push_back the
	}						    //entire path
	else{	//look at vertices adjacent to the vertex we looking at
		for(int i= 0; i<(int)ajlist[find(s)].e.size();i++){
			int j=find(ajlist[find(s)].e[i].s);
				if(!ajlist[j].visited)
					cout<<"";
					Find_All_Paths_Until(ajlist[j].name, d,
					path_index,build_edge(find(s),i));
		}
	}
	path_index--;
	ajlist[find(s)].visited = false;//unmark the vertex
}

/*
 * build_degrees(int count, string a)
 * prepare paths to be added to the path list
 */
paths Graph::build_paths(int count, string a)
{
	paths temp;
	temp.length=count;
	temp.path=a;
	return temp;
}

/*
 * build_edge(int index, int i)
 * prepare fragment of paths to be added onto the path
 */
string Graph::build_edge(int index, int i)
{
	string edge1 =" +- "+ajlist[index].e[i].c;
	string edge2 =" -> "+ajlist[index].e[i].s;
	string edge = edge1+edge2;
	return edge;

}

/*
 * printpath()
 * print out all paths
 */
void Graph::printpath()
{
	for(int i=0; i <(int)all_paths.size(); i++){
		cout<<all_paths.at(i).path<<endl;
	}
}

/*
 * print_shortest_path
 * print out the shortest path
 */
void Graph::print_shortest_path()
{
	int i = find_min();
	if(!all_paths.empty()){
		cout<<all_paths.at(i).path<<endl;
	}
	else return;
}

/*
 * find_min()
 * locate the shortest path, return the index of the shortest path in the array
 * the store all the paths
 */
int Graph::find_min()
{
	int min = 0;
	for (int i  = 1; i<(int)all_paths.size(); i++){
	    if (all_paths[i].length < all_paths[min].length){
	        min = i;
	    }
	}
	return min;
}

/*
 * expand()
 * expand the adjacency list
 */
void Graph::expand()
{
	adj *biggerarray = new adj[capacity*2];
	for(int i = 0; i<used; i++){
		biggerarray[i] = ajlist[i];
	}
	delete[] ajlist;
	ajlist = biggerarray;
	capacity = capacity*2;
}

/*
 * expand_path()
 * expand the path list
 */
void Graph::expand_path()
{
	string *biggerarray = new string[path_capacity*2];
	for(int i = 0; i<path_used; i++){
		biggerarray[i] = path[i];
	}
	delete[] path;
	path = biggerarray;
	path_capacity = path_capacity*2;
}

/*
 * find(string n)
 * find the index of a given string in adjacency list, return -1 when not found
 */
int Graph::find(string n)
{
	for(int i = 0; i<used; i++){
		if(ajlist[i].name == n){
			return i;
		}
	}
	return -1;
}
