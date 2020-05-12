/* Gary Zeri
 ID: 2321569
 zeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _BST_H_
#define _BST_H_

#include "bst_node.h"
#include "doubly_linked_list.h"

using namespace std;

//allows for specification of two values, both the key and value for the entries of the tree
template <class k, class v>
class BST {

	public:
		BST();
		~BST();	

		int Size();
		bool Empty();
		BSTNode<k,v>* Root();
		DoublyLinkedList<v>* Positions();	
		bool Find(k key, v &value);
		bool Put(k key, v value);
		bool Erase(k key);
	private:
		void DeleteNodes(BSTNode<k,v>* node);
		void GeneratePositionList(BSTNode<k,v>* node, DoublyLinkedList<v>* positionList);
		BSTNode<k,v>* InternalSearch(k key, BSTNode<k,v>** parentNode = NULL);
		void InternalDelete(BSTNode<k,v>* deletionNode, BSTNode<k,v>* parentNode);		
		BSTNode<k,v>* FindSuccessor(BSTNode<k,v>* node, BSTNode<k,v>** parentNode);

		BSTNode<k,v>* root;	
		int size;	
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
BST<k,v>::BST(){
	this->root = NULL;
	this->size = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
BST<k,v>::~BST(){
	
	BSTNode<k,v>* tempNode = root;
	root = NULL;

	DeleteNodes(tempNode);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
int BST<k, v>::Size(){
	return size;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
bool BST<k,v>::Empty(){
	return (root==NULL);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
BSTNode<k,v>* BST<k,v>::Root(){
	return root;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
DoublyLinkedList<v>* BST<k,v>::Positions(){
	
	DoublyLinkedList<v>* positionList = new DoublyLinkedList<v>;

	GeneratePositionList(root, positionList);

	return positionList;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
bool BST<k,v>::Find(k key, v &value){

	BSTNode<k,v>* node = InternalSearch(key);

	if(node == NULL)
		return false;
	
	value = node->value;
	return true;	
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
bool BST<k,v>::Put(k key, v value) {

	cout << "Put Function" << endl;

	BSTNode<k,v>* newNode = new BSTNode<k,v>(key, value);
	BSTNode<k,v>* insertLocation = NULL;

	cout << "Created a new node" << endl;

	//check if the node is alreadly located in the tree
	//if it is, return false to signify the new node was not added to the tree
	if(InternalSearch(key, &insertLocation) != NULL)
		return false;		

	cout << "internal search completed" << endl;
	//check if the root node is being put into the tree
	//otherwise determine whether the node is being placed to the right or left of the insert location
	if(insertLocation == NULL){
		this->root = newNode;
		this->root->isRoot = true;
		cout << "inside of first if" << endl;
	}
	else if(key > insertLocation->key)
		insertLocation->right = newNode;
	else
		insertLocation->left = newNode; 
	
	++size;
	cout << "Sucessful Put function " << endl;	
	return true;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
template <class k, class v>
bool BST<k,v>::Erase(k key) {
	
	BSTNode<k,v>* parentNode = NULL;
	BSTNode<k,v>* deletionNode = InternalSearch(key, &parentNode);

	//signify that the node to be deleted was not found in the tree
	if(deletionNode == NULL)
		return false;

	InternalDelete(deletionNode, parentNode);
	
	return true; 
}


//---------------------------------------------------------------------------------

template <class k, class v>

//deletes all the node that is passed into the function as well as 
//all the children of the specified node
void BST<k,v>::DeleteNodes(BSTNode<k,v>* node){
	
	if(node == NULL)
		return;

	BSTNode<k,v>* leftChild = node->left;
	BSTNode<k,v>* rightChild = node->right;

	node->left = NULL;
	node->right = NULL;

	delete node;

	DeleteNodes(leftChild);
	DeleteNodes(rightChild); 
}

//---------------------------------------------------------------------------------

template <class k, class v>

//position list generated using an inorder traveersal
void BST<k,v>::GeneratePositionList(BSTNode<k,v>* node, DoublyLinkedList<v>* positionList){
	
	if(node == NULL)
		return;

	positionList->InsertTail(node->value);
	GeneratePositionList(node->left, positionList);
	GeneratePositionList(node->right, positionList);
}

//---------------------------------------------------------------------------------

template <class k, class v>
BSTNode<k,v>* BST<k,v>::InternalSearch(k key, BSTNode<k,v>** parentNode){

	cout <<  "Inside of internal search" << endl;
	
	BSTNode<k,v>* tempNode = this->root;
	cout << "created temp node" << endl;
	cout << (tempNode == NULL) << endl;
	while(tempNode != NULL && key != tempNode->key){

		cout << "inside of internal search" << endl;
		if(parentNode != NULL)
			*parentNode = tempNode;

		if(key > tempNode->key)
			tempNode = tempNode->right;
		else
			tempNode = tempNode->left;
	}

	cout << "completed the internal search function" << endl;
	
	return tempNode;
}

//---------------------------------------------------------------------------------

template <class k, class v>
void BST<k,v>::InternalDelete(BSTNode<k,v>* deletionNode, BSTNode<k,v>* deletionParentNode){

	BSTNode<k,v>* newChild = NULL;
	BSTNode<k,v>* successorNode = NULL;
	BSTNode<k,v>* successorParentNode = NULL;
	
	//check all the possible deletion cases for the tree

	//case where there are two children for the node
	//find the smallest value from the right sub tree, the sucessor
	if(deletionNode->left != NULL && deletionNode->right != NULL){
		successorNode = FindSuccessor(deletionNode, &successorParentNode);
		newChild = new BSTNode<k,v>(successorNode->key, successorNode->value);
	}
	//check the case where the node has only one child
	else if(deletionNode->left == NULL)
		newChild = deletionNode->right;
	else
		newChild = deletionNode->left;	

	//give parent the new child
	//first check if changin the root to the child
	//check if left or right child of the parent is being deleted
	//right child deletion logic
	if(deletionParentNode == NULL){
		this->root = NULL;
		
		//check to ensure that tree is not being made empty by deleting the root
		if(newChild != NULL){
			this->root = newChild;
			this->root->isRoot = true;
		}
	}
	else if(deletionNode->key > deletionParentNode->key)
		deletionParentNode->right = newChild;
	//left logic
	else
		deletionParentNode->left =  newChild;	
	
	//check clean up should be performed when a node that had two children was deleted
	if(successorNode != NULL){
		newChild->right = deletionNode->right;
		newChild->left = deletionNode->left; 		

		//change the new child key to the deletion key 
		//to allow the removal of the successor node to occur correctly
		//then give the new child its original key
		k key = newChild->key;
		newChild->key = deletionNode->key;	
		InternalDelete(successorNode, newChild);
		newChild->key = key;
	}

	//delete the node to be deleted
	deletionNode->left = NULL;
	deletionNode->right = NULL;
	delete deletionNode; 
	--size;		
}

//---------------------------------------------------------------------------------

template <class k, class v>
BSTNode<k,v>* BST<k,v>::FindSuccessor(BSTNode<k,v>* node, BSTNode<k,v>** parentNode){

	//sucessor is found by going to the right of the current node, and then going all the way down to the left
	
	*(parentNode) = node;
	node = node->right;
	
	while(node->left != NULL){
		*(parentNode) = node;
		node = node->left;
	}

	return node;
}

#endif
