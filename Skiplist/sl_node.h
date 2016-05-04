#ifndef SL_NODE_H
#define SL_NODE_H

//Define skiplist node
struct SL_Node {
	int key;
	SL_Node** forward;

	SL_Node(int l, int k);
	~SL_Node();
};

typedef SL_Node* SL_Node_Ptr;

#endif
