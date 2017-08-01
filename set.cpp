#include <iostream>
#include <string>
#include "set.h"

using namespace std;

Set::Set()
{
	capacity = SET_INIT_CAPACITY;
	class_size = 0;
	roster = new string[SET_INIT_CAPACITY];
}

Set::~Set()
{
//	cerr<<"in destructor"<<endl;
//	print_roster();
	delete[] roster;
//	cerr<<"leave destructor"<<endl;
}

void Set::print_roster()
{
	for (int i = 0; i < class_size; i++) {
		cout << roster[i] <<endl;
	}
}

bool Set::add(string student_name)
{
	for (int i = 0; i < class_size; i++){
		if(is_exist(student_name)){
			return false;
		}
	}
	if (class_size >=capacity){
		expand();
	}

	roster[class_size] = student_name;
	class_size ++;

	return true;
}

bool Set::is_exist(string student_name)
{
	for (int i = 0; i < class_size; i++){
		if(roster[i] == student_name){
			return true;
		}
	}
	return false;
}

int Set::get_class_size()
{
	return class_size;
}

string Set::get_name(int index)
{
	return roster[index];
}

void Set::set_name(int index, string name)
{
	roster[index] = name;
}

void Set::expand()
{
	string *biggerarray = new string[capacity*2];
	for(int i =0; i < capacity; i++){
		biggerarray[i] = roster[i];
	}
	cerr<<"delete roster from set expand"<<endl;
	delete[] roster;
	roster = biggerarray;
	capacity *= 2;
}







