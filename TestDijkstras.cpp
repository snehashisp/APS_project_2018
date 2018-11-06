#include<bits/stdc++.h>
#include "Binomial-Heap.h"

/*
Input:
9
14
1 2 4
1 8 8
2 8 11
2 3 8
3 9 2
3 4 7
3 6 4
4 5 9
4 6 14
5 6 10
6 7 2
7 9 6
7 8 1
8 9 7

Output:
0 4 12 19 21 11 9 8 14
*/

int main(int argc, char const *argv[]){
	int list_size;
	node *node_list = get_data(list_size);
	int source;
	scanf("%d",&source);
	int *djk = dijkstra_bino(node_list,list_size,source-1);
	for(int i=0;i<list_size;i++)
		cout<<djk[i]<<" ";


	return 0;
}
