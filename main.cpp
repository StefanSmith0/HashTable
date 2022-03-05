#include <iostream>
#include <cstring>
#include "Node.h"
#include "names.h"

using namespace std;

Node* newNode(int nodeNum, Names* names);
void printList(Node* current);

int main() {
  Names* names = new Names();
  Node* head;
  for(int i = 0; i < 4; i++) {
    Node* temphead = head;
    head = newNode(i, names);
    if(temphead != NULL) {
      head->setNext(temphead);
    }
  }
  printList(head);
  
  delete names;
  return 0;
}

void printList(Node* current) {
  if(current == NULL) {
    return;
  }
  cout << endl;
  cout << "Name: " << current->getFirst() << " " << current->getLast() << endl;
  cout << "ID: " << current->getid() << endl;
  cout << "GPA: " << current->getgpa() << endl;
  if(current->getNext() != NULL) {
    printList(current->getNext());
  }
}

Node* newNode(int id, Names* names) {
  char firstName[30];
  names->randFirst(firstName);
  char lastName[30];
  names->randLast(lastName);
  float randgpa = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4)); //random float by John Dibling
  Node* node = new Node();
  node->setFirst(firstName);
  node->setLast(lastName);
  node->setid(id);
  node->setgpa(randgpa);
  return node;
}
