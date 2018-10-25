#include <bits/stdc++.h>
using namespace std;
typedef long l;
typedef struct Node Node;
struct Node
{
	l value;
	l degree;
	struct Node *parent;
	struct Node *child;
	struct Node *sibling;
};

//print BTree
void printTree(Node *root){ 
    while(root!=NULL){ 
        cout<<root->value << " "; 
        printTree(root->child); 
        root=root->sibling; 
    } 
} 


//print Bheap
void printHeap(list<Node*> heap) 
{ 
	cout<<"-------------------------\n";
    list<Node*> ::iterator it; 
    it = heap.begin(); 
    while (it != heap.end()){ 
        printTree(*it); 
        cout<<endl;
        it++; 
    } 
    cout<<"-------------------------\n";
} 

//create a bew BTree with 0 degree
Node * newNode(l value){
	Node * newNode=(Node *)malloc(sizeof(Node));
	newNode->value=value;
	newNode->degree=0;
	newNode->parent=NULL;
	newNode->child=NULL;
	newNode->sibling=NULL;
	return newNode;
}

//merge 2 BTrees having same degree
Node * merge2BTrees(Node * first, Node * second){
	if(first->value > second->value )
		swap(first, second);
	//change parent of second
	second->parent=first;
	//change sibling of second
	second->sibling=first->child;
	//change child of parent
	first->child=second;
	// increment the degree of parent
	first->degree+=1;
	return first;

}

//merge 2 heaps into a new heap with nondecending order of degrees of BTrees
list<Node*> merge(list<Node*> heap1, list<Node*> heap2){
	list<Node*> newHeap;
	list<Node*> :: iterator it1=heap1.begin();
	list<Node*> :: iterator it2=heap2.begin();
	while(it1!=heap1.end()&&it2!=heap2.end()){
		if((*it1)->degree<=(*it2)->degree){
			newHeap.push_back(*it1);
			it1++;
		}
		else{
			newHeap.push_back(*it2);
			it2++;
		}
	}
	while(it1!=heap1.end()){
		newHeap.push_back(*it1);
		it1++;
	}
	while(it2!=heap2.end()){
		newHeap.push_back(*it2);
		it2++;
	}
	cout<<"-----------------------------\n";
	printHeap(newHeap);
	cout<<"-----------------------------\n";
	return newHeap;
}

//make adjustments to assure one BTree corresponding to one degree(not more)
//cases
	//case1: if degree of adjacent nodes are different -> move forward
	
	//case 2: if degree of adjacent nodes are same
		//2-a
			// if degree of node next to next of current node is same as current->move forward
		//2-b else
			//merge BTrees corresponding to current and next
list<Node*> adjust(list<Node*> heap){
	list<Node *>:: iterator it1, it2, it3;
	it1=heap.begin();
	it2=it1;
	it3=it1;
	list<Node *> newHeap;
	if(heap.size()<=1)
		return heap;
	if(heap.size()==2){
		it2++;
		it3=heap.end();
	}
	else{
		it2++;
		it3=it2;
		it3++;
	}
	while(it1!=heap.end()){
		//case1
		if(it2==heap.end())
			it1++;
		else if((*it1)->degree!=(*it2)->degree){
			it1++;
			it2++;
			if(it3!=heap.end())
				it3++;
		}
		else{ //case 2-a
			if(it3!=heap.end()&&(*it1)->degree==(*it3)->degree){
				it1++;
				it2++;
				it3++;
			}
			else{	//case 2-b
	            *it1=merge2BTrees(*it1,*it2); 
	            it2=heap.erase(it2); 
	            if(it3!=heap.end()) 
	                it3++; 
			}
		}
	}
	return heap;
}

//insert a new node(BTree with 0 degree) in BHeap
list<Node *> insert(list<Node*> heap,l value){
	Node * nNode=newNode(value);
	list<Node *> newHeap;
	newHeap.push_back(nNode);
	//merge return new list with Btrees in nondecending order of degree
	//adjust take care to avoid 2 BTrees with same degree
	return adjust(merge(heap, newHeap));
}

//return root node of BTree with minimum value :O(logn)
Node * findMin(list<Node*> heap){
	Node * heapMin=newNode(LONG_MAX);
	for (list<Node*> :: iterator i = heap.begin(); i != heap.end(); ++i)
		if((*i)->value<heapMin->value)
			heapMin=*i;
	return heapMin;
}	

//extract the minimum node
list<Node*> extractMin(list<Node*> heap){
	cout<<"In extractMin\n";
	Node *heapMin=findMin(heap);
	list<Node*> newHeap;//heap containing all trees other than tree with minnode
	list<Node*> :: iterator it=heap.begin();
	//create heap of all nodes other than tree with minnode
	while(it!=heap.end()){
		if(*it!=heapMin)
			newHeap.push_back(*it);
		it++;
	}
	//now create a heap with child of btree having minimun as its root
	Node *child=heapMin->child;
	Node *temp;
	list<Node*> heap2;//heap containing all subtrees of tree with minnode
	while(child!=NULL){
		temp=child;
		child=child->sibling;
		temp->sibling=NULL;
		heap2.push_front(temp);//to insert lower degree first
	}
	return adjust(merge(newHeap, heap2));
}
int main(int argc, char const *argv[]){
	
	list<Node *> heap;
    heap=insert(heap,10); 
    heap=insert(heap,20); 
    heap=insert(heap,30); 
  	heap=insert(heap,40); 
    heap=insert(heap,50); 
    heap=insert(heap,60); 
  
  	heap=insert(heap,70); 
  	heap=insert(heap,80); 
  	heap=insert(heap,90); 
  	heap=insert(heap,100); 
  	heap=insert(heap,102); 
  	heap=insert(heap,104); 
  	heap=insert(heap,105); 
  	heap=insert(heap,107); 
  	heap=insert(heap,109); 
  
    cout<<"Heap elements after insertion:\n"; 
    printHeap(heap); 
  
    Node *temp=findMin(heap); 
    cout << "\nMinimum element of heap "<< temp->value << "\n"; 

    heap=extractMin(heap);
    cout<<"Heap elements after min extract:\n"; 
    printHeap(heap); 

	return 0;
}