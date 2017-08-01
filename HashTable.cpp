/*
 * ===========================HashTable.cpp=========================
 * By: Zhu Jing Wang
 * Purpose:
 * The implementation of hash table. I'm using chained hash this time to deal
 * with collision, (so I don't have to expand my hash table and rehash). This
 * implementation allows the client to add things into the hash table, to print
 * out the entire hash table, to print out the value of keys, and to gain
 * access to the value of keys.
 */

#include <iostream>
#include "HashTable.h"
#include "hashfunc.h"

using namespace std;

/*
 * HashTable()
 * Constructor
 */
HashTable::HashTable()
{
	for (int i = 0; i < TSIZE; i++) {
		htable[i] = NULL;
	}
}
/*
 * ~HashTable()
 * Destructor
 */
HashTable::~HashTable()
{
	for (int i = 0; i < TSIZE; i++) {
		Node *temp;
		while (htable[i] != NULL){
			temp = htable[i];
			htable[i] = htable[i]->next;
			delete temp;
		}
		delete htable[i];
	}
}
/*
 * add(string k, string val)
 * add new info into the hashtable
 */
void HashTable::add(string k, string val)
{
	int index = hash_string(k) % TSIZE;

	if(htable[index] == NULL){//when nothing in the bucket
		add_helper(index,k,val);
	}
	else {
		Node *current = htable[index];
		if(current->key == k){
			current->value.push_back(val);//traverse to the
			return;
		}
		while(current->next != NULL){
			if(current->key == k){
				current->value.push_back(val);
				return;
			}
			current = current->next;
		}
		if(current->key == k){
			current->value.push_back(val);
			return;
		}
		add_helper(index,k,val);
	}
}
/*
 * add_helper(int index, string k, string val)
 * creates a new node to hold the info we need to add to the hashtable and link
 * it to where it belongs
 */
void HashTable::add_helper(int index, string k, string val)
{
	Node *entry = new Node;
	htable[index] = entry;
	entry->key = k;
	entry->value.push_back(val);
	entry->next = NULL;
}
/*
 * print_table()
 * print out the whole hashtable (I basically wrote this func to test if my
 * hashtable works)
 */
void HashTable::print_table()
{
	Node *current = NULL;;
	for (int i = 0; i < TSIZE; ++i) {
		current= htable[i];
		while (current != NULL) {
			cout<<current->key;
			for(int j=0; j< (int)current->value.size(); j++){
				cout<<" "<<current->value.at(j);
			}
			cout<<endl;
			current = current->next;
		}
	}
}
/*
 * print_value()
 * print out the value of a specific key
 */
void HashTable::print_value(string data)
{
	Node *current = NULL;
	for (int i = 0; i < TSIZE; ++i) {
		current= htable[i];
		while (current != NULL) {
			if(current->key == data){
				for(int j=0; j<(int)current->value.size(); j++){
					cout<<current->value.at(j)<<endl;
				}
			}
			current = current->next;
		}
	}
}
/*
 * get(string key)
 * access the value of a key we looking for, returns empty vector if key not
 * found
 */
vector<string> HashTable::get(string key)
{
	int index = hash_string(key) % TSIZE;

	if(htable[index] == NULL)
		return vector<string>();
	Node *current = htable[index];
	while(current->key != key){
		current = current->next;
		if(current == NULL)
			return vector<string>();
	}
	return current->value;
}

