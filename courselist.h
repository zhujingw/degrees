#ifndef COURSELIST_H_
#define COURSELIST_H_

#include "set.h"

struct Course {
	string course_number;
	Set roster;
};

class Course_list{
public:
	Course_list();
	~Course_list();

	bool add();
	bool is_exist();
	void print();
	int get_size();

private:
	static const int INIT_CAPACITY = 2;

	void expand();
	Course *class_list;
	int capacity;
	int list_size;
};

#endif
