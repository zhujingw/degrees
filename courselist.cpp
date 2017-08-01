#include <iostream>
#inclue "couselist.h"

using namespace std;

Course_list::Couse_list()
{
	capacity = INIT_CAPACITY;
	list_size = 0;
	class_list = new Course[INIT_CAPACITY];
}

Course_list::~Course_list()
{
	delete[] Course_list;
}

void Course_list::print()
{
	for(int i = 0; i < list_size; i++){
		for(int j = 0; j < )
	}
}

bool Course_list::add(string number, string name)
{
	for(int i  = 0; i < list_size; i++){
		if(is_exist(number)){
			return false;
		}
	}
	if (list_size >= capacity){
		expand();
	}

	class_list[list_size].course_number = number;
	class_list[list_size].class_roster.add(name);

	list_size ++;
	return true;
}

bool Course_list::is_exist(string number)
{
	for(int i = 0; i < list_size; i++){
		if(class_list[i].course_number = number){
			return true;
		}
	}
	return false;
}

int Course_list::get_size()
{
	return list_size;
}

void Course_list::expand()
{
	Course *biggerarray = new Course[capacity*2];
	for(int i = 0; i < capacity; i++){
		biggerarray[i].course_number = class_list[i].course_number;
		for(int j = 0; j < class_list[i].roster.size; j++){
//problematic		biggerarray[i].roster.set_name(j.class_list[i].roster.get_name(j));
		}
	}
	delete[] class_list;
	class_list = biggerarray;
	capacity *= 2;
}









