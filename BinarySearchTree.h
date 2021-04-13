#pragma once
namespace hfmn {
	class Heap;
	typedef struct {
		char chKey;
		int frequency;
	}chFrequency;
	class BSTreeNode
	{
	private:
		chFrequency value;
		BSTreeNode* left;
		BSTreeNode* right;
	public:
		BSTreeNode();
		BSTreeNode(char chKey, BSTreeNode* _left, BSTreeNode* _right);
		~BSTreeNode();
		void setValue(chFrequency set) { this->value.chKey = set.chKey; this->value.frequency = set.frequency; };
		chFrequency getValue() { return this->value; };
		char getKey() const { return this->value.chKey; };
		void setFrequency(int _frequency) { this->value.frequency = _frequency; };
		int getFrequency() const { return this->value.frequency; };
		bool updateFrequency() { return this->value.frequency += 1; };
		BSTreeNode* getLeft()  const { return this->left; };
		BSTreeNode* getRight() const { return this->right; };
		char setKey(char ch) { return this->value.chKey=ch; };
		void setLeft(BSTreeNode* set) { this->left = set; };
		void setRight(BSTreeNode* set) { this->right = set; };
		void Inorder(BSTreeNode* node);
		void Preorder(BSTreeNode* node);
		void Postorder(BSTreeNode* node);
		void printHuffman(BSTreeNode* root, int arr[], int index,int* charSizes);
		void printCodes(int* arr, int index);
	};
	class BSTree
	{
	private:
		BSTreeNode* root;
		int size = 0;
	public:
		BSTree() :root(nullptr) {};
		~BSTree();
		int getTreeSize() { return this->size; };
		bool findAndUpdate(char chKey);
		BSTreeNode* buildHuffmanTree(Heap floydHeap);
		void buildTreeFromFile(ifstream& inFile);
		void bstToArray(BSTreeNode* root, BSTreeNode** arr);
		BSTreeNode* getRoot() { return this->root; };
		BSTreeNode* Find(char chKey);
		void Insert(char chKey);
		void Delete(char chKey);
		BSTreeNode* deleteNode(BSTreeNode* root, char chKey);
	};
}

