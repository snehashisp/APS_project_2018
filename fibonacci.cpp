#include"fibonacci.h"

fibo_node *init_node(int key,void *data) {

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
	parent -> degree += child -> degree + 1;
	fibo_node *child_node = parent -> child;
	if(child_node == NULL) parent -> child = child;
	else add_to_list(child_node,child);

}

void remove_node(fibo_node *node) {

	if(node == NULL) return;
	if(node -> parent) {
		node -> parent -> degree -= 1;
		node -> parent -> mark = MARK;
	}
	if(node -> next == node) node -> parent -> child = NULL; 
	else remove_from_list(node);

}


void fibo_heap :: consolidate() {

	//get log of the number of nodes in the tree 
	int log_nodes = ceil(log((double)total_nodes)/log(2)) + 1;
	//Array to hold the different degree trees of the consolidated root list
	fibo_node *deg_array[log_nodes];
	//initialize to null
	for(int i = 0; i < log_nodes; i++) deg_array[i] = NULL;

	//iterate all the nodes in the head list
	fibo_node *iterator = min_node;
	while(iterator) {

		fibo_node *it = iterator;
		int deg = it -> degree;
		//succesively check if the current tree degree is already present in the degree list
		while(deg_array[deg] != NULL) {
			//Swap the node with the smaller key
			if(it -> key > deg_array[deg] -> key) {
				fibo_node *temp = it;
				it = deg_array[deg];
				deg_array[deg] = temp;
			}
			add_child(it,deg_array[deg]);
			deg_array[deg] = NULL;
			deg = it -> degree; 

		}
		//remove previous link
		iterator -> prev -> next = NULL;
		iterator = iterator -> next;

	}

	//recreate head list
	min_node = NULL;
	for(int i = 0 ; i < log_nodes; i++) {
		if(deg_array[i] != NULL) {
			if(min_node == NULL) {
				min_node = deg_array[i];
				min_node -> next = min_node ->prev = min_node;
			}
			else {
				add_to_list(min_node,deg_array[i]);
				if(min_node -> key > deg_array[i] -> key)
					min_node = deg_array[i];
			}
		}
	}
}

void fibo_heap :: insert(int key,void *data) {

	fibo_node *new_node = init_node(key,data);
	if(min_node == NULL) {
		min_node = new_node;
	}
	else {
		add_to_list(min_node,new_node);
		if(min_node -> key > key)
			min_node = new_node;
	}
	total_nodes++;
}

fibo_node *fibo_heap :: extract_min() {

	if(min_node == NULL) return NULL;
	fibo_node *child_node = min_node -> child,*temp;
	total_nodes--;

	while(child_node) {
		add_child(min_node,child_node);
		child_node -> prev -> next = NULL;
		child_node = child_node -> next;
	}

	if(min_node -> next == min_node) {
		fibo_node *temp = min_node;
		min_node = NULL;
	}
	else {
		temp = min_node;
		min_node = min_node -> next;
		remove_node(temp);
		consolidate();
	}
	return temp;

}

