#ifndef SKIPLIST_H
#define SKIPLIST_H

#define MAXLEVEL 14

const int FAILURE = -1;
const float PROB = 0.5;

#include <limits.h>
#include "sl_node.h"

const SL_Node_Ptr NIL = new SL_Node(1,ULONG_MAX);

int random_level();

//Define skiplist class
class Skiplist {

	friend void print_node(SL_Node* x);
	
	private:
		SL_Node_Ptr header;
		int level;
		int count; // number of keys or forward pointers accessed during search, insertion, or delete

	public:
		Skiplist();
		int search(int searchKey);
		void insert_node(int searchKey);
		void delete_node(int searchKey);
		void print_list();
		int get_count() {return count;}
};

#endif
