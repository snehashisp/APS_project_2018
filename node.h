#include<cstdio>
#include<vector>

struct node {
	
	int node_id;
	int current_dist;
	std::vector<std::pair<struct node *,int>> edge_list;

};

struct node *create_node(int node_id);
void insert_edge(struct node *start_node,struct node *end_node,int weight);
