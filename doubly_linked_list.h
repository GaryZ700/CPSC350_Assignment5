/* Gary Zeri
  ID: 2321569
  zeri@chapman.edu
  CPSC 250-02
  Assignment 4: Registrar's Office Simulation */

#ifndef DOUBLY_LINKED_LIST_H_
#define DOUBLY_LINKED_LIST_H_

#include <iostream>
#include <exception>

using namespace std;

template <class T>
class DoublyLinkedList{

	public:
		DoublyLinkedList(){
			this->size = 0;
			this->front = NULL;
			this->tail = NULL;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		DoublyLinkedList(const T &data){
			this->size = 0;
			this->tail = NULL;
			
			this->InsertFront(data);
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		~DoublyLinkedList(){
			Node *tempNode = front; 
			Node *nextNode;

			front = NULL;
			tail = NULL;

			while(tempNode != NULL){

				nextNode = tempNode->prev;
				tempNode->next = NULL;
				tempNode->prev = NULL;
				
				delete tempNode;

				tempNode = nextNode;	
			}
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		void InsertFront(const T &data){
		
			Node *newNode = new Node{data};

			if(!EmptyInsert(newNode)){
				front->next = newNode;
				newNode->prev = front;
				newNode->next = NULL;
				front = newNode;
			}
			
			++size;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		void InsertTail(const T &data){
		
			Node *newNode = new Node{data};
		
			if(!EmptyInsert(newNode)){	
				tail->prev = newNode;
				newNode->next = tail;
				newNode->prev = NULL;
				
				tail = newNode;
			}
	
			++size;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		const T& Front() const{
			EmptyError("can not return the front");
			return front->data;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		const T& Tail() const{
			EmptyError("can not return the tail value.");
			return tail->data;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		void RemoveFront(){
			EmptyError("can not remove the front node.");
			RemoveNode(front);
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		void RemoveTail(){
			EmptyError("can not return the tail node.");	
			RemoveNode(tail);
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		//note position uses computer counting, 
		//meeaning that first position in the list is at index 0	
	        void RemovePosition(int position){
			
			//error checking to ensure that the position to be deleted is valid
			if(position < 0 || position >= size)
				cout << endl << "Warning! Can not remove the node at position " << position << ", the node does not exist." << endl;			
			Node *tempNode = front;

			for(int i=0; i<position; ++i)
				tempNode = tempNode->prev;
	
			RemoveNode(tempNode); 
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		//returns an int representing the position of the item in the list
		//if -1 is returned, then the item is not in the list
		int Search(const T &data) const{
			
			Node *tempNode = front;
			int position = -1;
	
			while(tempNode != NULL){
				
				++position;
				
				if(tempNode->data == data)
					return position;
				
				tempNode = tempNode->prev;
			}
			return -1;	
		}
		
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		bool SearchPosition(int position, T &data){
			
			if(position < 0 || position > size)
				return false;

			Node *tempNode = front;

			for(int i=0; i<position; ++i)
				tempNode = tempNode->prev;
	
			data = tempNode->data;

			return true;			
		}
			

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		int Size() const{
			return size;
		}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
		bool Empty() const{
			return (size == 0);
		}

	//---------------------------------------------------------------------------------

	private:
		int size;
		struct Node{
			T data;
			Node *next;
			Node *prev;
		};
		Node *front;
		Node *tail;	
		
	//---------------------------------------------------------------------------------
		
		bool EmptyInsert(Node *newNode){
			if(!Empty())
				return false;
			
			front = newNode;
			tail = newNode;
			
			newNode->next = NULL;
			newNode->prev = NULL;

			return true;			
		}
		
	//---------------------------------------------------------------------------------
	
		void RemoveNode(Node *node){
	
			//determine if dealing with either the start, ending, or middle of the list
			//also check for the case where there is a single node
			if(node->next == NULL && node->prev == NULL){
				front = NULL;
				tail = NULL;	
			}
			else if(node->next == NULL){
				front = front->prev;
				front->next = NULL;
			}	
			else if(node->prev == NULL){
				tail = tail->next;
				tail->prev = NULL;
			}
			else{
				node->next->prev = node->prev;
				node->prev->next = node->next;
			}

			node->next = NULL;
			node->prev = NULL;
		
			delete node;
					
			--size;	
		}
	
	//---------------------------------------------------------------------------------

		void EmptyError(const string &errorMessage) const{
			if(Empty())
				cout << endl << "List is empty, " << errorMessage << endl;
		}
};

#endif //DOUBLY_LINKED_H_
