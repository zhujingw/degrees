#ifndef list_dynamic_array_h
#define list_dynamic_array_h

#include <iostream>
#include "set.h"
using namespace std;

struct Course{
	string course_name;
	Set course_roster;
};

class List{
public:
	List();
	~List();

	void add(string course, string student);
	bool is_exist(string course);
	void print_list();
	int get_list_size();
	Course get_list_at_index(int index);
	string get_course_name(int index);

private:
	static const int LIST_INIT_CAPACITY = 2;

	void expand();
	Course *list;
	int capacity;
	int list_size;

};

#endif
