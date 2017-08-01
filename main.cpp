/*
 * ========================main.cpp==============================
 * By: Zhu Jing Wang
 * Purposr:
 * This is a program that reads in two files (one student file, one ta file),
 * stores all the information, finds all connections among those people, and
 * maps one person to the other. The main data structures I use this time
 * are two chained hashtables, three vectors of strings, and one graph.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

#include "HashTable.h"
#include "Graph.h"

void readData1(char *argv[],HashTable &r, vector<string> &n, vector<string> &c);
void readData2(char *argv[],HashTable &t, vector<string> &n, vector<string> &c);
void push_back_helper(vector<string> &data, string n);
void CommandLine(vector<string> &n, vector<string> &c, HashTable &r,
							HashTable &t, Graph &g);
void roster(vector<string> &c, string data1, HashTable &r);
void taed(vector<string> &n, string data1, HashTable &t);
void paths(vector<string> &n, string data1, string data2, Graph &g);
void shortestpath(vector<string> &n, string data1, string data2, Graph &g);
void print(vector<string> &n, vector<string> &c, string command);
bool check_exist(vector<string> &data, string n);

int main(int argc, char *argv[])
{
	assert(argc>2);

	HashTable Rosters;
	HashTable CourseTAed;
	vector<string> names, courses, tas;
	Graph graph;

	//read in data
	readData1(argv, Rosters, names, courses);
	readData2(argv, CourseTAed, names, courses);

	//creat adjacency list
	graph.create_ajlist(names,Rosters,CourseTAed);

	//take in commands and process
	CommandLine(names, courses, Rosters, CourseTAed, graph);

	return 0;
}
/*
 * readData1(char *argv[],HashTable &r,vector<string> &n, vector<string> &c)
 * read-in students file and call functions to add info to hashtable and vector
 */
void readData1(char *argv[],HashTable &r,vector<string> &n, vector<string> &c)
{
	ifstream infile;
	string name, course, year;
	char delim1 = ':';
	char delim2 = '\n';

	infile.open(argv[1]);

	while(getline(infile,name,delim1)){
		getline(infile,course,delim1);
		getline(infile,year,delim2);
		course.append(year);
		push_back_helper(n,name);
		push_back_helper(c,course);
		r.add(course,name);
	}
	infile.close();

}
/*
 * readData2(char *argv[],HashTable &t, vector<string> &n, vector<string> &c)
 * read-in tas file and call functions to add info to hashtable and vector
 */
void readData2(char *argv[],HashTable &t, vector<string> &n, vector<string> &c)
{
	ifstream input;
	string name, course, year;
	char delim1 = ':';
	char delim2 = '\n';

	input.open(argv[2]);

	while(getline(input,name,delim1)){
		getline(input,course,delim1);
		getline(input,year,delim2);
		course.append(year);
		push_back_helper(n,name);
		push_back_helper(c,course);
		t.add(name,course);
	}
	input.close();
}
/*
 * push_back_helper(vector<string> &data, string n)
 * helper function of standard vector push_bach, check existence before push back
 */
void push_back_helper(vector<string> &data, string n)
{
	int size = static_cast<int>(data.size());
	for(int i = 0; i < size; i++){
		if(data.at(i) == n){
			return;
		}
	}
	data.push_back(n);

}
/*
 * CommandLine(vector<string> &n, vector<string> &c, HashTable &r,
 * 							 HashTable &t, Graph &g)
 * take in commands from commandline, process command and call related functions
 * to do what commands ask for
 */
void CommandLine(vector<string> &n, vector<string> &c, HashTable &r,
		                                         HashTable &t, Graph &g)
{
	string command, data1, data2;
	cin >> command;
	if(command == "ls" or command == "lc"){
		print(n, c, command);
		return;
	}
	cin >> data1;
	if(command == "roster"){
		roster(c,data1,r);
		return;
	}
	if(command == "taed"){
		taed(n,data1,t);
		return;
	}
	cin >>data2;
	if(command == "paths"){
		paths(n,data1,data2,g);
		return;
	}
	if(command == "shortestpath"){
		shortestpath(n,data1,data2,g);
		return;
	}
	else return;
}
/*
 * shortestpath(vector<string> &n, string data1, string data2, Graph &g)
 * call related functions to print out shortest path, if either name not found,
 * print out to user "Student not found"
 */
void shortestpath(vector<string> &n, string data1, string data2, Graph &g)
{
	if(check_exist(n,data1) and check_exist(n,data2)){
		g.Find_All_Paths(data1,data2);
		g.print_shortest_path();
	}
	else if(!check_exist(n,data1) or !check_exist(n,data2)){
		cout<<"Student not found"<<endl;
	}
}
/*
 * paths(vector<string> &n, string data1, string data2, Graph &g)
 * call related functions to print out all paths, if either student not found,
 * print out to user "Student not found"
 */
void paths(vector<string> &n, string data1, string data2, Graph &g)
{
	if(check_exist(n,data1) and check_exist(n,data2)){
		g.Find_All_Paths(data1,data2);
		g.printpath();
	}
	else if(!check_exist(n,data1) or !check_exist(n,data2)){
		cout<<"Student not found"<<endl;
	}
}
/*
 * taed(vector<string> &n, string data1, HashTable &t)
 * call related functions to print out list of courses the person taed, if name
 * not found, print out to user "Student not found"
 */
void taed(vector<string> &n, string data1, HashTable &t)
{
	if(check_exist(n,data1)){
		t.print_value(data1);
	}
	else if(!check_exist(n,data1)){
		cout<<"Student not found"<<endl;
	}
}
/*
 * roster(vector<string> &c, string data1, HashTable &r)
 * call related functions to print out roster of a course, if course not found,
 * print out to user "Course not found"
 */
void roster(vector<string> &c, string data1, HashTable &r)
{
	if(check_exist(c,data1)){
		r.print_value(data1);
	}
	else if(!check_exist(c,data1)){
		cout<<"Course not found"<<endl;
	}
}
/*
 * print(vector<string> &n, vector<string> &c, string command)
 * process ls lc command, print out either list of names, or list of courses
 */
void print(vector<string> &n, vector<string> &c, string command)
{
	if(command == "ls"){
	int nsize = static_cast<int>(n.size());

		for(int i = 0; i < nsize; i++){
			cout << n.at(i) <<endl;
		}
	}
	if(command == "lc"){
	int csize = static_cast<int>(c.size());

		for(int i = 0; i < csize; i++){
			cout << c.at(i) <<endl;
		}
	}
}
/*
 * check_exist(vector<string> &data, string n)
 * check if data has been added already, to avoid duplicates
 */
bool check_exist(vector<string> &data, string n)
{
	int size = static_cast<int>(data.size());
	for(int i = 0; i < size; i++){
		if(data.at(i) == n){
			return true;
		}
	}
	return false;
}




