#include "linked_list.hpp"

// Free the memory taken by the list(destructor)
LinkedList::~LinkedList() {
	if (head == nullptr) return;

	Node *p, *q;
	for (p = head; p != nullptr; p = q) {
		q = p->next;
		delete p;
	}
}


void LinkedList::sortedInsert(int _value) {
	Node *newNode = new Node(_value);  //we declare a new node with the value
	Node * aux = head; // and the auxiliaries, both one that points to the list head
	Node **aux2 = &head;  // and another that can modify the list head, if suitable
	
	//while we have not reached the place of insertion( the data is bigger)
	while (aux != nullptr && aux->data < newNode->data) {
		aux2 = &aux->next;// cycle through
		aux = aux->next;
	}
	*aux2 = newNode; //otherwise insert at the place in which we were
	newNode->next = aux;
}
//print the elements
void LinkedList::print() {
	if (head == nullptr) return;

	Node *p;
	for (p = head; p != nullptr; p = p->next) {
		std::cout << p->data << " ";
	}
}