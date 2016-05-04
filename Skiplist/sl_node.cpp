#include "sl_node.h"

#define NULL 0

// SL_Node implementation

SL_Node::SL_Node(int l=1, int k=0)
{
	key=k;
	forward=new SL_Node*[l];
}

SL_Node::~SL_Node()
{
	delete [] forward;
}
