#include"node.h"
#include<cmath>


struct veb_node {

	int sub_max = -1;
	int sub_min = -1;
	node *max = NULL;
	node *min = NULL;
	
	int u;
	int upper;
	int lower;

	veb_node *summary = NULL;
	veb_node **cluster = NULL;

};

class veb_tree {

	veb_node *head = NULL;
	node *dummy = NULL;
	void init(veb_node *head,int u);
	void show_tree(veb_node *head);
	int insert(veb_node *head,int nkey,node *new_node);
	void delnode(veb_node *head,int key);
	//veb_node *find_node(veb_node *head,int key);	

	public:

	int universe;
	int insert(node *new_node);
	void delnode(node *delnode);
	node *get_min();

	void show_tree();
	void init(int u,node *dummy);
};