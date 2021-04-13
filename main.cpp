#include "GlobalHeader.h"
using namespace hfmn;
//Nir Jacob ID 316252931
//Tomer Porat ID 206260804
int main()
{
	////OPEN FILE
	string fileName;
	cout << "Please enter the file name: " << endl;
	cin >> fileName;
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {//If there was an error in opening the file.
		cout << "invalid input" << endl;
		exit(1);
	}

	///////BUILD TREE FROM FILE
	BSTree fileTree;
	fileTree.buildTreeFromFile(inFile);
	int btsSize = fileTree.getTreeSize();

	////////USE HUFFMAN ON THE TREE
	//Build min heap from the binary search tree
	Heap floydHeap(fileTree, btsSize);
	BSTree huffmanTree;
	BSTreeNode* huffmanTRoot = huffmanTree.buildHuffmanTree(floydHeap);

	////////PRINT THE HUFFMAN ENCODING
	cout << "Character encoding: "<< endl;
	int* codes = new int[floydHeap.getSize()];//Auxiliary array to represent the bit encoding.
	int fileSize = 0;
	huffmanTRoot->printHuffman(huffmanTRoot, codes, 0,&fileSize);
	delete[] codes;
	////////CALCULATE THE FILE SIZE
	cout << "Size of the file is" << " " << fileSize << " " << "bytes";

	inFile.close();//Close the file.
	return 0;
}
