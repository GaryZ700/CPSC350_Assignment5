/* Gary Zeri
 ID: 2321569
 Nzeri@chapman.edu
 CPSC 250-02
 Assignment 5: Building a Database with Binary Search Trees
*/

#ifndef _BST_NODE_H_
#define _BST_NODE_H_

#include <iostream>

using namespace std;

template<class k, class v>
class BSTNode{

	public:
		BSTNode(k key, v value);
		~BSTNode();
		
		bool IsRoot();
		bool IsExternal();
		
		BSTNode<k,v>* left;
		BSTNode<k,v>* right; 	
		k key;
		v value;
		bool isRoot;
		
};

template <class k, class v>
BSTNode<k,v>::BSTNode(k key, v value){
	this->key = key;
	this->value = value;	

	this->left = NULL;
	this->right = NULL;

	this->isRoot = false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
BSTNode<k,v>::~BSTNode(){
	this->left = NULL;
	this->right = NULL;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
bool BSTNode<k,v>::IsRoot(){
	return isRoot;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

template <class k, class v>
bool BSTNode<k,v>::IsExternal(){
	return ( left == NULL && right == NULL );
}

#endif
