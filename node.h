#include<cstdio>
#include<vector>
#include<climits>

struct node {
	
	int node_id;
	int current_dist = 0;
	std::vector<std::pair<node *,int>> edge_list;

};

node *create_node(int node_id);
void insert_edge(node *start_node,node *end_node,int weight);
