/*
  Stefan Smith
  3/13/2022
  Hash Table

  Citations:
  - Anxious Alligator - https://www.codegrepper.com/profile/anxious-alligator-bx1nkddr8shy
  - John Dibling - https://stackoverflow.com/users/241536/john-dibling
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <math.h>
#include "Node.h"
#include "names.h"

using namespace std;

Node* newNode(int nodeNum, Names* names);
void print(Node* (&table)[], vector<int> &keyList);
void add(Node* newNode, Node* (&table)[], vector<int> &keyList);
void deleteNode(char* deleteName, Node* (&table)[], vector<int> &keyList);
long hash(char *str);
float roundto2(float value);

int main() {
  Names* names = new Names();
  Node* table[101] = {nullptr};
  vector<int> keyList;
  char input[30];
  for(int i = 0; i < 4; i++) {
    add(newNode(i, names), table, keyList);
  }
  Node* test = new Node();
  print(table, keyList);
  cout << "Pick a child: ";
  cin.getline(input, 30);
  deleteNode(input, table, keyList);
  delete names;
  return 0;
}

//Delete a Node by name
void deleteNode(char* deleteName, Node* (&table)[], vector<int> &keyList) {
  int deleteKey = ::hash(deleteName) % 101;
  bool success = false;
  if(table[deleteKey] == nullptr) { //No element with input name
    cout << "No student with name: " << deleteName << endl;
  }
  else if(table[deleteKey]->getNext() == nullptr) { //Element found, no elements in linkedlist
    delete table[deleteKey];
    table[deleteKey] = nullptr;
    cout << "Student deleted" << endl;
    success = true;
  }
  else { //Element found, elements in linkedlist
    Node* current = table[deleteKey]->getNext();
    Node* next = current->getNext();
    Node* prev = table[deleteKey];
    while(::hash(current->getFirst()) != ::hash(deleteName)) { //Go through linkedlist until hashes match
      if(next == nullptr) { //End of list check
	cout << "An element was found, but the student was not in the linkedlist" << endl;
	return;
      }
      current = next;
      next = current->getNext();
    }
    prev->setNext(next);
    delete current;
    cout << "Student deleted" << endl;
    success = true;
  }
  if(success) {
    for(int i = 0; i < keyList.size(); i++) { //If node deleted, remove from keyList
      if(keyList[i] == deleteKey) {
	keyList.erase(keyList.begin() + (i - 1));
      }
    }
  }
}

void print(Node* (&table)[], vector<int> &keyList) {
  Node* current;
  Node* next;
  for(int i = 0; i < keyList.size(); i++) { //Print through hash table
    current = table[keyList[i]];
    next = current->getNext();
    cout << "Student: " << current->getFirst() << " " << current->getLast() << endl;
    cout << "ID: " << current->getid() << endl;
    cout << "GPA: " << current->getgpa() << endl;
    while(next != nullptr) { //Print through linked list
      i++;
      cout << "Student: " << next->getFirst() << " " << next->getLast() << endl;
      cout << "ID: " << next->getid() << endl;
      cout << "GPA: " << next->getgpa() << endl;
      current = next;
      next = current->getNext();
    }
    cout << endl;
  }
}

//Rounds a float to 2 decimal places
float roundto2(float value) {
  return round(value * pow(10.0f, 2)) / pow(10.0f, 2); //Round to Decimal by Anxious Alligator
}

//Adds a Node to the hash table
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

//Makes a new Node with random values
Node* newNode(int id, Names* names) { 
  char firstName[30];
  names->randFirst(firstName);
  char lastName[30];
  names->randLast(lastName);
  float randgpa = roundto2(1 + static_cast <float> (rand()) /
		   (static_cast <float> (RAND_MAX/(4-1)))); //random float by John Dibling
  Node* node = new Node();
  node->setFirst(firstName);
  node->setLast(lastName);
  node->setid(id);
  node->setgpa(randgpa);
  return node;
}

//Hash function
long hash(char *str) { //djb2 by Dan Bernstein
  long hash = 5381;
  int c;
  while (c = *str++) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash;
}
