#include <iostream>
#include <cstddef>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "skiplist.h"

const int MAXNODES = 128;  // Maximum number of nodes to be inserted and deleted

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	Skiplist list;

	for (int i=0; i<MAXNODES; i++) {
		list.insert_node((int)floor(fabs(i*sin(i))));
	}

	cout << "Number of elements accessed during last insert: " << list.get_count() << endl;	
	//list.print_list();

	int random_num = rand()%MAXNODES;

	if (list.search(random_num) != FAILURE)
		cout << "search for key " << random_num << " succeeded" << endl;
	else
		cout << "search for key " << random_num << " failed" << endl;

	cout << "Number of elements accessed during search: " << list.get_count() << endl;	

	for (int i=0; i<MAXNODES; i++) {
		list.delete_node((int)floor(fabs(i*sin(i))));
	}

	cout << "Number of elements accessed during last delete: " << list.get_count() << endl;	

	return 1;
}
