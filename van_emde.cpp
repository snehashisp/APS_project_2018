#include"van_emde.h"
#define debug(A) ;
//printf("%d\n",A)

void veb_tree :: init(int u,node *dummy) {
	head = new veb_node;
	universe = u;
	init(head,u);
	this -> dummy = dummy;
}
void veb_tree :: init(veb_node *node,int u) {

	if(u == 2) {
		node -> u = 2;
		return;
	}
	else {

		node -> u = u;
		int p = (int)(log(u)/log(2));
		node -> lower = (int)pow(2,p/2);
		node -> upper = (int)pow(2,ceil(p/2.0));
		node -> cluster = new veb_node*[node -> upper];
		for(int i = 0; i < node -> upper; i++) {
			node -> cluster[i] = new veb_node;
			init(node -> cluster[i],node -> lower);
		}
		node -> summary = new veb_node;
		init(node -> summary,node -> upper);
	}
}

void veb_tree :: show_tree() {
	show_tree(head);
}
void veb_tree :: show_tree(veb_node *head) {
 
	if(head == NULL) return;
	else {
		printf(" %d(%d)(%d) %d %d, [",head -> u,head -> upper,head -> lower, head -> min ? head -> sub_min : -1, head -> max ? head -> sub_max : -1);
		node * temp = head -> min;
		while(temp) {
			printf("o");
			temp = temp -> next;
		}
		printf("|");
		temp = head -> max;
		while(temp) {
			printf("o");
			temp = temp -> next;
		}
		printf("] ");
		if(head -> summary) show_tree(head->summary);
		for(int i = 0; i < head -> upper; i++) {
			show_tree(head -> cluster[i]);
		}
	}
}

node *veb_tree::get_min() {
	return head -> min;
}

int veb_tree :: insert(node *new_node) {
	return insert(head,new_node->current_dist,new_node);
}
int veb_tree :: insert(veb_node *head,int nkey,node *new_node) {

	if(head -> min == NULL) {
		head -> min = head -> max = new_node;
		head -> sub_min = head -> sub_max = nkey;
	}
	else if(head -> sub_min == nkey) {
		if(new_node == dummy) return 0;
		new_node -> next = head -> min -> next;
		if(head -> min -> next) head -> min -> next -> prev = new_node;
		head -> min -> next = new_node;
		new_node -> prev = head -> min;
	}	
	else if(head -> sub_max == nkey) {
		if(new_node == dummy) return 0;
		new_node -> next = head -> max -> next;
		if(head -> max -> next) head -> max -> next -> prev = new_node;
		head -> max -> next = new_node;
		new_node -> prev = head -> max;
	}
	else {
		int ret;
		if(nkey < head -> sub_min) {
			node * temp = head -> min;
			head -> min = new_node;
			new_node = temp;
			int temp2 = nkey;
			nkey = head -> sub_min;
			head -> sub_min = temp2;
		}
		if(head -> u > 2) {
			if(head -> cluster[nkey / head -> lower] -> min == NULL) {
				insert(head -> summary,nkey / head -> lower,dummy);
			}
			ret = insert(head -> cluster[nkey / head -> lower],nkey % head -> lower,new_node);
		}
		if(nkey > head -> sub_max) {
			head -> sub_max = nkey;
			head -> max = new_node;
		}
		return ret;
	}

}

void veb_tree :: delnode(node *del_node) {
	if(del_node -> prev == NULL)
		delnode(head,del_node->current_dist);
	else {
		del_node -> prev -> next = del_node -> next;
		if(del_node -> next) 
			del_node -> next -> prev = del_node -> prev;
	}
	del_node -> next = del_node -> prev = NULL;
	
}

void veb_tree :: delnode(veb_node *head,int nkey) {

	if(head -> sub_min == head -> sub_max) {
		head -> min = head -> min -> next;
		if(head -> min) head -> min -> prev = NULL;
		head -> max = head -> min;
	}
	else if (head -> u == 2) {
		if(nkey == head -> sub_min) {
			head -> min = head -> min -> next;
			if(!head -> min) {
				head -> sub_min = 1;
				head -> min = head -> max;
			}
			else head -> min -> prev = NULL;
		}
		else {
			head -> max = head -> max -> next;
			if(!head -> max) {
				head -> sub_max = 0;
				head -> max = head -> min;
			}
			else head -> max -> prev = NULL;
		}

	}
	else {
		if(nkey == head -> sub_min) {

			head -> min = head -> min -> next;
			if(head -> min) {
				head -> min -> prev = NULL;
				return;
			}
			int min_cluster = head -> summary -> sub_min;
			nkey = min_cluster * head -> lower + head -> cluster[min_cluster] -> sub_min;
			head -> min = head -> cluster[min_cluster] -> min;
			head -> cluster[min_cluster] -> min = dummy;
			head -> sub_min = nkey;
		}
		delnode(head -> cluster[nkey / head -> lower],nkey % head -> lower);
		if(head -> cluster[nkey / head -> lower] -> min == NULL) {
			delnode(head -> summary,nkey / head -> lower);

			if(nkey == head -> sub_max) {
				node *sum_max = head -> summary -> max;
				if(sum_max == NULL) {
					head -> max = head -> min;
					head -> sub_max = head -> sub_min;
				}
				else {
					int sumx = head -> summary -> sub_max;
					head -> max = head -> cluster[sumx] -> max;
					head -> sub_max = sumx * head -> lower + head -> cluster[sumx] -> sub_max;

				}
			}
		}
		else if(nkey == head -> sub_max) {
			head -> max = head -> cluster[head -> sub_max / head -> lower] -> max;
			head -> sub_max = (head -> sub_max / head -> lower) * head->lower + head -> cluster[head -> sub_max /head -> lower] -> sub_max;
		}

	}

}

