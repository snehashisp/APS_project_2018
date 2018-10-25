#include"node.h"
#include<climits>


struct node *create_node(int node_id) {

	struct node *newnode = new node;
	newnode->node_id = node_id;
	newnode->current_dist = INT_MAX;
	return new_node;
}

void insert_edge(struct node *start_node,struct node *end_node,int weight) {

	start_node->edge_list.push_back(pair<struct node*,int>(end_node,weight));
	end_node->edge_list.push_back(pair<struct node*,int>(start_node,weight));

}

