#include <stdlib.h>
#include "skiplist.h"

#include <iostream>
using namespace std;

int random_level()
{
	int lvl=1;
	while (((double)rand())/RAND_MAX < PROB && lvl < MAXLEVEL)
		lvl++;
	return lvl;
}

//Skiplist implementation

void print_node(SL_Node* x)
{
	cout << x->key << '|' << x;
}

Skiplist::Skiplist()
{
	level = 1;
	count = 0;
	header = new SL_Node(MAXLEVEL,0);
	for (int i=0; i<MAXLEVEL; i++) {
		header->forward[i]=NIL;
	}
}

int Skiplist::search(int searchKey)
{
	count = 0;  // Number of times a key or forward pointer is accessed in skiplist during search
	SL_Node_Ptr x = header;
	
	for (int i=level-1; i>-1; i--) {
		while ((++count) && (unsigned long int)x->forward[i]->key < (unsigned long int)searchKey)
			x = x->forward[i];
			count++;
	}

	x = x->forward[0];
	count++;

	if ((++count) && x->key == searchKey)
		return x->key;
	else
		return FAILURE;

}

void Skiplist::insert_node(int searchKey)
{
	SL_Node_Ptr update[MAXLEVEL];
	SL_Node_Ptr x = header;
	count = 0;  // Number of times a key or forward pointer is accessed in skiplist during insert
	
	for(int i=level-1; i>-1; i--) {
		while ((++count) && (unsigned long int)x->forward[i]->key < (unsigned long int)searchKey) {
			x = x->forward[i];
			count++;
 		}
		update[i] = x;
	}

	x = x->forward[0];
	count++;
	
	if ((++count) && ((unsigned long int)x->key != (unsigned long int)searchKey))
	{
		int lvl = random_level();
		if (lvl > level)
		{
			for (int i=level; i<lvl; i++) {
				update[i] = header;
			}
			level = lvl;
		}

		x = new SL_Node(lvl,searchKey);

		for (int i=0; i<lvl; i++) {
			x->forward[i] = update[i]->forward[i];
			count++;
			update[i]->forward[i] = x;
		}
	}
}

void Skiplist::delete_node(int searchKey)
{
	SL_Node_Ptr update[MAXLEVEL];
	SL_Node_Ptr x = header;
	count = 0;  // Number of times a key or forward pointer is accessed in data structure during delete
	
	for(int i=level-1; i>-1; i--) {
		while ((++count) && (unsigned long int)x->forward[i]->key < (unsigned long int)searchKey) {
			x = x->forward[i];
			count++;
		}
		update[i] = x;
	}

	x = x->forward[0];
	count++;
	
	if ((++count) && (unsigned long int)x->key == (unsigned long int)searchKey)
	{
		for (int i=0; i<level; i++) {
			if (update[i]->forward[i] != x)
				break;
			else {
				update[i]->forward[i] = x->forward[i];
				count++;
			}
		}

		delete x;

		while (level>1 && header->forward[level] == NIL && (++count))
			level--;
	}
}

void Skiplist::print_list()
{
	SL_Node_Ptr x = header;

	cout << "HEADER-->";
	x = x->forward[0];
	while ((unsigned long int)x->key != (unsigned long int)NIL->key) {
		print_node(x);
		cout << "-->";
		x = x->forward[0];
	}
	cout << "NIL" << endl;
	
}
