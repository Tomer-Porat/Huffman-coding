#include "GlobalHeader.h"

namespace hfmn {
	Heap::Heap(int max) 
	{
		data = new BSTreeNode*[max];
		for(int i=0;i<max;i++){
			data[i] = new BSTreeNode;
		}
		this->maxSize = max;
		this->allocated = 0;
		this->heapSize = 0;
	}
	Heap::~Heap() 
	{
		while (this->heapSize > 1)
		{
			this->DeleteMin();
		}
		
	}
	Heap::Heap(BSTree fileTree , int n)
	{//Build heap with n numbers from the binary search tree.
		maxSize = n;
		heapSize = n;
		//Create an array from the binary search tree:
		BSTreeNode** fileTreeArr = new BSTreeNode*[fileTree.getTreeSize()];
		for(int i=0; i<fileTree.getTreeSize() ;i++){
			fileTreeArr[i] = new BSTreeNode;
		}

		fileTree.bstToArray(fileTree.getRoot() ,fileTreeArr);

		data = fileTreeArr;
		allocated = 1;
		for(int i=n/2-1; i>=0; i--){//Build the heap:
			FixHeap(i);
		}

	}
	void Heap::Swap(BSTreeNode** child, BSTreeNode** parent)
	{
		BSTreeNode* temp = *child;
		*child = *parent;
		*parent = temp;
	}
	void Heap::FixHeap(int node) { //Fixes the heap that has node as root.
		int min = node;
		int left = Left(node);
		int right = Right(node);
		//Find maximum among nodes, left and right.
		if ((left < heapSize) && (data[left]->getFrequency() < data[node]->getFrequency()))
			min = left;
		if ((right < heapSize) && (data[right]->getFrequency() < data[min]->getFrequency()))
			min = right;
		//Swap values if necessary ,and continue
		//fixing the heap towards the leaves.
		if (min != node) {
			Swap(&data[node], &data[min]);
			FixHeap(min);
		}	
	}
	BSTreeNode* Heap::DeleteMin() {
		if (heapSize < 1)
			cout << "ERROR. Heap is empty." << endl;
		BSTreeNode* min = data[0];
		heapSize--;
		data[0] = data[heapSize];//Update the heap root.
		FixHeap(0);
		return (min);
	}
	void Heap::Insert(BSTreeNode* item){
		if(this->heapSize == this->maxSize){
			cout<<"ERROR";
		}
		int i = heapSize;
		heapSize++;
		while ((i > 0) && (data[Parent(i)]->getFrequency() > item->getFrequency()))
		{//If the parent is bigger than the item we want to insert, 
			data[i] = data[Parent(i)];
			i = Parent(i);
		}
		data[i] = item;
	}
	int Heap::Parent(int node)
	{
		return ((node - 1) / 2);
	}
	int Heap::Left(int node)
	{
		return (2 * node + 1);
	}
	int Heap::Right(int node)
	{
		return (2 * node + 2);
	}
	bool Heap::makeEmpty() 
	{
		while (this->heapSize > 1)
		{
			this->DeleteMin();
		}
		return true;
	}
}