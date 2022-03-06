#include <iostream>
#include <cstring>
#include <vector>
#include "Node.h"
#include "names.h"

using namespace std;

Node* newNode(int nodeNum, Names* names);
void print(Node* (&table)[], vector<int> &keyList);
void add(Node* newNode, Node* (&table)[], vector<int> &keyList);
long hash(char *str);

int main() {
  Names* names = new Names();
  Node* head;
  Node* table[101] = {nullptr};
  vector<int> keyList;
  for(int i = 0; i < 4; i++) {
    add(newNode(i, names), table, keyList);
  }
  print(table, keyList);
  delete names;
  return 0;
}

void print(Node* (&table)[], vector<int> &keyList) {
  Node* current;
  Node* next;
  for(int i = 0; i < keyList.size(); i++) {
    current = table[keyList[i]];
    next = current->getNext();
    cout << i << ": " << current->getFirst() << endl;
    while(next != nullptr) {
      i++;
      cout << i << ": " << next->getFirst() << endl;
      current = next;
      next = current->getNext();
    }
  }
}

void add(Node* newNode, Node* (&table)[], vector<int> &keyList) {
  int key = ::hash(newNode->getFirst()) % 101;
  keyList.push_back(key);
  if(table[key] == nullptr) {
    table[key] = newNode;
  }
  else {
    cout << "Collision, adding to linked list..." << endl;
    Node* current = table[key];
    Node* next = current->getNext();
    while(next != nullptr) {
      current = next;
      next = current->getNext();
    }
    current->setNext(newNode);
  }
  cout << "Student: " << newNode->getFirst() << endl;
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
