#include <iostream>
#include <cstring>
#include "Node.h"
#include "names.h"

using namespace std;

Node* newNode(int nodeNum, Names* names);
void printList(Node* current);
void add(Node* newNode, Node* (&table)[]);
long hash(char *str);

int main() {
  Names* names = new Names();
  Node* head;
  Node* table[101] = {nullptr};
  for(int i = 0; i < 4; i++) {
    add(newNode(i, names), table);
  }
  //  printList(head);
  delete names;
  return 0;
}

void printList(Node* current) {
  if(current == nullptr) {
    return;
  }
  cout << endl;
  cout << "First name: " << current->getFirst() << endl;
  cout << "Last name: " << " " << current->getLast() << endl;
  cout << "ID: " << current->getid() << endl;
  cout << "GPA: " << current->getgpa() << endl;
  if(current->getNext() != NULL) {
    printList(current->getNext());
  }
}

void add(Node* newNode, Node* (&table)[]) {
  long key = ::hash(newNode->getFirst()) % 101;
  if(table[key] == nullptr) {
    table[key] = newNode;
  }
  else {
    cout << "Collision, adding to linked list..." << endl;
    Node* current = table[key];
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    current->setNext(newNode);
  }
  cout << "Student: " << newNode->getFirst();
  cout << " " << newNode->getLast() << endl;
  cout << " pushed to: " << key << endl;
}

Node* newNode(int id, Names* names) {
  char firstName[30];
  names->randFirst(firstName);
  char lastName[30];
  names->randLast(lastName);
  float randgpa = 1 + static_cast <float> (rand()) /
    (static_cast <float> (RAND_MAX/(4-1))); //random float by John Dibling
  Node* node = new Node();
  node->setFirst(firstName);
  node->setLast(lastName);
  node->setid(id);
  node->setgpa(randgpa);
  return node;
}

//djb2 by Dan Bernstein
long hash(char *str) {
  long hash = 5381;
  int c;
  while (c = *str++) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}
