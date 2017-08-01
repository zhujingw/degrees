#include <iostream>
#include <string>
#include "list_dynamic_array.h"


using namespace std;

List::List()
{
	capacity = LIST_INIT_CAPACITY;
	list_size = 0;
	list = new Course[LIST_INIT_CAPACITY];
}

List::~List()
{
//	for(int i = 0; i < list_size; i++){
//		delete[] list[i].course_roster;
//	}
	delete[] list;
}

void List::print_list()
{
	for (int i = 0; i < list_size; i++){
		cout << list[i].course_name <<endl;
	}
}
void List::add(string course, string student)
{
//	for (int i = 0; i < list_size; i++){
	if (list_size >= capacity){
		expand();
	}
	if(is_exist(course)){
		for(int i = 0; i < list_size; i++){
			if(list[i].course_name == course){
				list[i].course_roster.add(student);
				list[i].course_roster.print_roster();
			}
		}
	}

	else{
		list[list_size].course_name = course;
		list[list_size].course_roster.add(student); //might have problem
		list_size ++;
	}

}

Course List::get_list_at_index(int index)
{
	return list[index];
}

bool List::is_exist(string course)
{
	for (int i = 0; i < list_size; i++){
		if(list[i].course_name == course){
			return true;
		}
	}
	return false;
}

int List::get_list_size()
{
	return list_size;
}

string List::get_course_name(int index)
{
	return list[index].course_name;
}

void List::expand()//need to check
{
	Course *biggerarray = new Course[capacity*2];
	for(int i = 0; i < capacity; i++){
		biggerarray[i] = list[i];
	}
	cerr<<"delete list in list expand"<<endl;
	delete[] list;
	list = biggerarray;
	capacity *= 2;
}







