#include"fibonacci.h"
#define debug(I)  printf("\ndebug %d\n",I);
#define debug2(I) printf(" %d ",I);

int print_tree(fibo_node *root) {

	int num = 0;
	if(root == NULL) return 0;
	else {
		fibo_node *next = root;
		do {
			//printf("(%d %d)",root -> key,root -> data -> node_id);
			num += print_tree(next -> child);
			next = next -> next;
		}while(next != root);
	}
	return num + 1;
}

fibo_node *init_node(int key,node *data) {

	fibo_node *new_node = new fibo_node;
	new_node -> parent = new_node -> child = NULL;
	new_node -> next = new_node -> prev = new_node;
	new_node -> mark = UNMARK;
	new_node -> degree = 0;
	new_node -> key = key;
	new_node -> data = data;
	return new_node;

}

void add_to_list(fibo_node *list_head, fibo_node *node) {

	node -> next = list_head;
	node -> prev = list_head -> prev;
	list_head -> prev -> next = node;
	list_head -> prev = node;

}

void *remove_from_list(fibo_node *node) {

	node -> prev -> next = node -> next;
	node -> next -> prev = node -> prev;

}

void add_child(fibo_node *parent,fibo_node *child) {

	if(child == NULL) return;
	child -> parent = parent;
	child -> mark = UNMARK;
	parent -> degree += 1;
	fibo_node *child_node = parent -> child;
	child -> next = child -> prev = child;
	if(child_node == NULL) parent -> child = child;
	else add_to_list(parent -> child,child);

}

void fibo_heap :: remove_node(fibo_node *node) {

	fibo_node *parent = node -> parent;
	//if(node == min_node) min_node = NULL;
	if(parent) {
		parent -> degree -= 1;
		if(parent -> degree == 0) parent -> child = NULL;
		else parent -> child = node -> next;
	}
	remove_from_list(node);
	node -> parent = NULL;
	node -> next = node -> prev = node;
	total_nodes--;
}


void fibo_heap :: consolidate() {

	printf("consolidate calld\n");
	show_tree();
	//get log of the number of nodes in the tree 
	int log_nodes = ceil(log((double)total_nodes)/log(2)) + 1;
	printf("total_nodes %d log_nodes %d\n",total_nodes,log_nodes);
	//Array to hold the different degree trees of the consolidated root list
	fibo_node *deg_array[log_nodes];
	//initialize to null
	for(int i = 0; i < log_nodes; i++) deg_array[i] = NULL;

	//iterate all the n//odes in the head list
	fibo_node *iterator = min_node;
	while(iterator) {

		fibo_node *it = iterator;
		if(iterator -> next == iterator) iterator = NULL;
		else iterator = iterator -> next;

		int deg = it -> degree;	
		remove_from_list(it);
		it -> parent = NULL;
		it -> next = it -> prev = it;
		//remove previous link and move to the next element in head
		//succesively check if the current tree degree is already present in the degree list
		while(deg_array[deg] != NULL) {
			//Swap the node with the smaller key
			if(it -> key > deg_array[deg] -> key) {
				fibo_node *temp = it;
				it = deg_array[deg];
				deg_array[deg] = temp;
			}
			//printf("%d ",deg);
			add_child(it,deg_array[deg]);
			deg_array[deg] = NULL;
			deg += 1; 
		}
		deg_array[deg] = it;
	}

	//recreate head list
	min_node = NULL;
	for(int i = 0 ; i < log_nodes; i++) {
		if(deg_array[i] != NULL) {
			if(min_node == NULL) {
				min_node = deg_array[i];
				min_node -> next = min_node -> prev = min_node;
			}
			else {
				add_to_list(min_node,deg_array[i]);
				if(min_node -> key > deg_array[i] -> key) 
					min_node = deg_array[i];
			}
		}
	}
	printf("consolidate end\n");
	show_tree();

}

void fibo_heap :: insert(fibo_node *new_node) {

	new_node -> mark = UNMARK;
	new_node -> parent = NULL;
	if(min_node == NULL) {
		min_node = new_node;
		new_node -> prev = new_node -> next = new_node;
	}
	else {
		add_to_list(min_node,new_node);
		if(min_node -> key > new_node -> key)
			min_node = new_node;
	}
	total_nodes++;
}

fibo_node *fibo_heap :: extract_min() {

	if(min_node == NULL) return NULL;
	fibo_node *cur_node = min_node,*temp;
	total_nodes--;

	while(cur_node -> child) {
		temp = cur_node -> child;
		remove_node(cur_node -> child);
		insert(temp);
	}
	//show_tree();
	if(min_node -> next == min_node) {
		temp = min_node;
		min_node = NULL;
	}
	else {
		temp = min_node;
		min_node = min_node -> next;
		remove_from_list(temp);
		consolidate();
	}

	if(min_node == NULL) debug(10);
	return temp;

}

void fibo_heap :: decrease_key(fibo_node *node,int key) {

	printf("Decrease key start %d %d\n",node -> key,key);
	show_tree();
	node -> key = key;
	fibo_node *parent = node -> parent,*temp;
	if(parent == NULL) {
		if(min_node -> key > node -> key)
			min_node = node;
	}
	else if(parent -> key > key) {
		remove_node(node);
		insert(node);
		while(parent && parent -> mark == MARK) {
			temp = parent;
			parent = parent -> parent;
			remove_node(temp);
			insert(temp);
		}
		if(parent) parent -> mark = MARK;
		else temp -> mark = MARK;
	}
	printf("Decrease key end\n");
	show_tree();
}

void fibo_heap :: show_tree() {

	int tn = 0;
	if(min_node == NULL) return;
	fibo_node *root = min_node;
	do {
		//printf("(%d %d)",root -> key,root -> data -> node_id);
		tn += print_tree(root -> child);
		//printf("\n");
		root = root -> next;
	}while(root != min_node);
	printf("\n[%d]\n",tn);
}

bool fibo_heap :: is_empty() {
	if(min_node == NULL) return true;
	else return false;
}
