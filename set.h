#ifndef SET_H_
#define SET_H_

#include <string>
using namespace std;

class Set {
public:
	Set();
	~Set();

	bool add(string student_name);
	bool is_exist(string student_name);
	void print_roster();
	int get_class_size();
	string get_name(int index);
	void set_name(int index, string name);

private:
	static const int SET_INIT_CAPACITY = 2;

	void expand();
	string *roster;
	int capacity;
	int class_size;
};

#endif
