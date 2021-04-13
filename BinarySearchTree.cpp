#include "GlobalHeader.h"
namespace hfmn {
	class BSTree;
	class BSTreeNode;
	//BSTreeNode Methods

	BSTreeNode::BSTreeNode(){
		this->left = nullptr;
		this->right= nullptr;
		this->value.frequency = 0;
	}
	BSTreeNode::BSTreeNode(char chKey, BSTreeNode* _left, BSTreeNode* _right) {
		chFrequency newFreq;
		newFreq.chKey = chKey;
		newFreq.frequency = 1;
		this->value = newFreq;
		this->left = _left;
		this->right = _right;
	}
	BSTreeNode::~BSTreeNode() {
	}

	void BSTreeNode::Postorder(BSTreeNode* node)
	{
		
		if (node == nullptr)
			return;
		Postorder(node->left);
		Postorder(node->right);

	}
	void BSTreeNode::Inorder(BSTreeNode* node)
	{ 
		if (node == nullptr)
			return;

		Inorder(node->left);
		if (node->getKey() != '\0')
		{
			cout << "The Key is: (" << node->getKey() << ")";
			cout << ", Frequency: " << node->getFrequency() << endl;
		}
		cout << "1";
		Inorder(node->right);
	}
	void BSTreeNode::Preorder(BSTreeNode* node)
	{
		if (node == nullptr)
			return;
		cout << node->getFrequency() << " ";
		Preorder(node->left);
		Preorder(node->right);
	}

	//BSTree Methods	
	void BSTree::buildTreeFromFile(ifstream& inFile)
	{
		char ch = '0';
		inFile >> noskipws >> ch;
		while(!inFile.eof()){
			if (!inFile.good()) {
				cout << "invalid input" << endl;
				exit(1);
			}
			this->Insert(ch);
			inFile >> ch;
		}                   
	}
	BSTree::~BSTree()
	{
		BSTreeNode* temp = root;
		while (temp != nullptr)
		{
			if(temp){
				temp = deleteNode(temp->getLeft(), temp->getKey());
			}
			if(temp){
				temp = deleteNode(temp->getRight(), temp->getKey());
			}
		}
	}
	bool BSTree::findAndUpdate(char chKey)
	{//Add 1 to the node frequency
		BSTreeNode* temp = root;
		while (temp != nullptr) {
			if (chKey == (temp->getKey())) {
				temp->updateFrequency();
				return true;
			}
			else if (chKey < temp->getKey()) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}

		return false;
	}

	void BSTree::Insert(char chKey) 
	{
		//If the char already exists, find it and update the frequency
		if (this->findAndUpdate(chKey)) {
			return;
		}
		this->size+=1;
		//Else, create new node:
		BSTreeNode* temp = root;
		BSTreeNode* parent = nullptr;
		BSTreeNode* newNode;

		while (temp != nullptr) {
			parent = temp;
			if (chKey < (temp->getKey())) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}
		newNode = new BSTreeNode(chKey, nullptr, nullptr);
		if (parent == nullptr) {
			root = newNode;
		}
		else if (chKey < parent->getKey()) {
			parent->setLeft(newNode);
		}
		else {
			parent->setRight(newNode);
		}
	}

	BSTreeNode* BSTree::Find(char chKey) 
	{
		BSTreeNode* temp = root;
		while (temp != nullptr) {
			if (chKey == (temp->getKey())) {
				return temp;
			}
			else if (chKey < temp->getKey()) {
				temp = temp->getLeft();
			}
			else {
				temp = temp->getRight();
			}
		}
		return nullptr;
	}
	void BSTree::Delete(char chKey)
	{
		BSTreeNode* toDel;
		toDel = Find(chKey);
		if(toDel){
			deleteNode(toDel, chKey);
		}
		else {
			cout << "Error: Key Not Found";
		}
	}

	BSTreeNode* BSTree::deleteNode(BSTreeNode* root, char chKey)
	{
		if (root == NULL)
			return root;

		if (root->getKey() > chKey) {
			root->setLeft(deleteNode(root->getLeft(), chKey));
			return root;
		}
		else if (root->getKey() < chKey) {
			root->setRight(deleteNode(root->getRight(), chKey));
			return root;
		}
		if (root->getLeft() == NULL) {
			BSTreeNode* temp = root->getRight();
			delete root;
			return temp;
		}
		else if (root->getRight() == NULL) {
			BSTreeNode* temp = root->getLeft();
			delete root;
			return temp;
		}
		else {

			BSTreeNode* currParent = root;

			BSTreeNode* curr = root->getRight();
			while (curr->getLeft() != NULL) {
				currParent = curr;
				curr->setLeft(curr->getLeft());
			}
			if (currParent != root)
				currParent->setLeft(curr->getRight());
			else
				currParent->setRight(curr->getRight()) ;

			root->setKey(curr->getKey());
			
			delete curr;
			return root;
		}
	}
	void BSTree::bstToArray(BSTreeNode* root, BSTreeNode** arr)
	{//creating an array from the file binary search tree to later make into a heap
		static int index = 0;
		if (root == NULL)
		{
			return;
		}
		bstToArray(root->getLeft(), arr);
		arr[index]->setValue(root->getValue());
		index++;
		bstToArray(root->getRight(), arr);
	}
	BSTreeNode* BSTree::buildHuffmanTree(Heap floydHeap){
		//using the floydHeap we build a huffman tree by deleting the minimum 2 nodes in the heap
		//and adding them to a sub-tree and by connecting all the sub-trees we create a huffman coded root
		BSTreeNode* node;
		while (floydHeap.getSize() > 1)
		{//creating a sub-tree each iteration
			node = new BSTreeNode;
			node->setLeft(floydHeap.DeleteMin());
			node->setRight(floydHeap.DeleteMin());
			//summing the frequencies of the 2 minimus nodes in the heap to make them the root of the new node
			node->setFrequency(node->getLeft()->getFrequency() + node->getRight()->getFrequency());
			floydHeap.Insert(node);
		}//we return the huffman root in the end
		return floydHeap.DeleteMin();
	}
	 void BSTreeNode::printHuffman(BSTreeNode* root,int codes[], int index,int* fileSize){
		  
		// if left root exist we save 0 and move on to the leafs
		if (root->left) 
		{
			codes[index] = 0;
			printHuffman(root->left,codes, index + 1,fileSize);
		}
		// if left root exist we save 1 and move on to the leafs
		if (root->right)
		{
			codes[index] = 1;
			printHuffman(root->right, codes, index + 1,fileSize);
		}
		// when we find a leaf we sum its frequency * number of ones and zeros hes coded in to calculate to total file size
		//and then we print its code by printing the zeros and ones we saved in the array so far
		if (root->left == nullptr && root->right == nullptr)
		{
			if (root->getKey() == '\n') {//New line
				cout << "\\n";
			}
			if (root->getKey() == '\t') {//Tab
				cout << "\\t";
			}
			else
			{
				cout << root->getKey();
			}
			if (!index) {
				*fileSize = root->getFrequency();
			}
			else{
				*fileSize += (root->getFrequency()) * index;
			}
			printCodes(codes, index);
		}
	 }
	 void BSTreeNode::printCodes(int* arr, int index)
	 {
		cout << " - ";
		for(int i=0;i<index;i++)
		{
			cout << arr[i];
		}
		cout << "\n";
	 }


}


