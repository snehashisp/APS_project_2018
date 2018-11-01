#include<cstdio>
#include"node.h"
#include<cmath>
	
#define MARK 1
#define UNMARK 0
#define swap

struct fibo_node {

	fibo_node *next = this,*prev = this;
	fibo_node *parent = NULL,*child = NULL;

	int mark = UNMARK;
	int degree = 0;

	int key = INT_MAX;
	node *data = NULL;

};

void add_to_list(fibo_node *list_head,fibo_node *node);
void *remove_from_list(fibo_node *node);
fibo_node *init_node(int key,node *data);
void add_child(fibo_node *parent,fibo_node *child);
int print_tree(fibo_node *root);

class fibo_heap {

	fibo_node *min_node = NULL;
	int total_nodes = 0;
	void consolidate();

	public:

	bool is_empty();
	void show_tree();
	void insert(fibo_node *new_node);
	void remove_node(fibo_node *node);
	fibo_node *extract_min();
	void decrease_key(fibo_node *node,int key);

};
