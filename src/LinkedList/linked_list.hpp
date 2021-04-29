#include<iostream>

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

// defining the nodes in the list
typedef struct Node {
	int data;
	Node *next = nullptr;

	Node(int _data) { data = _data; }
} Node;

//defining the linked list and its constructors
class LinkedList{
  public:
	LinkedList() {};
	~LinkedList();

	void sortedInsert(int);
	void print();
  private:
	Node *head = nullptr;
}; //LinkedList

#endif //LINKED_LIST_HPP