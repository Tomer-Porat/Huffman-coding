#pragma once
namespace hfmn {
	class BSTree;
	class BSTreeNode;
	class Heap {
	private:
		BSTreeNode** data;  //Points to the data array.
		int maxSize;        //Max size of heap.
		int heapSize;       //Current size of heap.
		int allocated;      //1 if heap allocated memory.
		static int Left(int node);
		static int Right(int node);
		static int Parent(int node);
		void FixHeap(int node);
	public:
		Heap(int max);
		Heap(BSTree fileTree, int n);
		~Heap();
		int getSize() {return this->heapSize;};
		void addSize() { this->heapSize += 1; };
		BSTreeNode* DeleteMin();
		void Swap(BSTreeNode** child, BSTreeNode** parent);
		void Insert(BSTreeNode* item);
		bool isEmpty() { return (!this->heapSize); };
		bool makeEmpty();
	};
}
