#include<cstdio>
#include"node.h"
#include<cmath>
	
#define MARK 1
#define UNMARK 0
#define swap

struct fibo_node {

	fibo_node *next,*prev;
	fibo_node *parent,*child;

	int mark;
	int degree;

	int key;
	void *data;

};

void add_to_list(fibo_node *list_head,fibo_node *node);
void *remove_from_list(fibo_node *node);
fibo_node *init_node(int key,void *data);
void add_child(fibo_node *parent,fibo_node *child);
void remove_node(fibo_node *node);

class fibo_heap {

	fibo_node *min_node;
	int total_nodes;
	void consolidate();

	public:

	void insert(int key,void *data);
	fibo_node *extract_min();
	void decrease_key(fibo_node *node);
	void delete_node(fibo_node *node);

};
