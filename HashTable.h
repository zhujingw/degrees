/*
 * ======================HashTable.h=============================
 * By: Zhu Jing Wang
 * header file for HashTable class
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include "hashfunc.h"

using namespace std;

struct Node{
	string key;
	vector<string> value;
	Node *next;
};

class HashTable
{
public:
	//constructor
	HashTable();
	//destructor
	~HashTable();

	//adding entries into hash table
	void add(string k, string val);
	//print out the entire table
	void print_table();
	//print of value for a key
	void print_value(string data);
	//gain access to value of a key
	vector<string> get(string key);

private:
	static const int TSIZE = 1024;

	//hashtable
	Node *htable[TSIZE];
	//add's helper function
	void add_helper(int index, string k, string val);

};
#endif
