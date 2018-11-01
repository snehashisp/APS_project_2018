#include"node.h"


node *create_node(int node_id) {

	node *newnode = new node;
	newnode->node_id = node_id;
	newnode->current_dist = 0;
	return newnode;
}

void insert_edge(node *start_node,node *end_node,int weight) {

	start_node->edge_list.push_back(std::pair<node*,int>(end_node,weight));
	end_node->edge_list.push_back(std::pair<node*,int>(start_node,weight));

}

