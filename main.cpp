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
void add(Node* newNode, Node* (&table)[], vector<int> &keyList, int tableSize);
void deleteNode(char* deleteName, Node* (&table)[], vector<int> &keyList, int tableSize);
long hash(char *str);
float roundto2(float value);
void deleteTable(Node* (&table)[], vector<int> &keyList);
//void rehash(Node* (&nottable)[], Node* (&(*table))[], vector<int> &keyList, int newSize);

int main() {
  int tableSize = 101;
  Names* names = new Names();
  Node* nottable[tableSize] = {nullptr};
  Node* (*table)[tableSize] = &nottable;
  vector<int> keyList;
  char input[30];
  bool running = true;
  for(int i = 0; i < 12; i++) { //make random students
    add(newNode(i, names), *table, keyList, tableSize);
  }
  while(running) {
    cout << "Command: ";
    cin.getline(input, 30);
    if(!strcmp(input, "quit")) {
      running = false;
    }
    else if(!strcmp(input, "delete")) {
      cout << "Student to delete: ";
      cin.getline(input, 30);
      deleteNode(input, *table, keyList, tableSize); 
    }
    else if(!strcmp(input, "print")) {
      print(*table, keyList);
    }
    else if(!strcmp(input, "add")) {
      cout << "Add not developed." << endl;
    }
  }
  deleteTable(*table, keyList);
  delete names;
  return 0;
}
/*
Node* rehash(Node* (&nottable)[], Node* (*table)[], vector<int> &keyList, int newSize) {
  Node* current;
  Node* newTable[newSize];
  table = &newTable;
  for(int i = 0; i < keyList.size(); i++) {
    current = table[keyList[i]];
    if(current != nullptr) {
      
    }
  }
  }*/

//Deletes all Nodes in table.
void deleteTable(Node* (&table)[], vector<int> &keyList) {
  Node* current;
  for(int i = 0; i < keyList.size(); i++) {
    current = table[keyList[i]];
    if(current == nullptr) {
      return;
    }
    else if(current->getNext() == nullptr) {
      delete current;
      table[keyList[i]] == nullptr;
    }
    else {
      Node* next;
      while(current != nullptr) {
	next = current->getNext();
	delete current;
	current = next;
      }
      table[keyList[i]] == nullptr;
    }
  }
}

//Delete a Node by name - this sometimes screws things up
void deleteNode(char* deleteName, Node* (&table)[], vector<int> &keyList, int tableSize) {
  int deleteKey = ::hash(deleteName) % tableSize;
  if(table[deleteKey] == nullptr) { //No element with input name
    cout << "No student with name: " << deleteName << endl;
  }
  else if(table[deleteKey]->getNext() == nullptr) { //Element found, no elements in linkedlist
    delete table[deleteKey];
    table[deleteKey] = nullptr;
    cout << "Student deleted" << endl;
    for(int i = 0; i < keyList.size(); i++) { //Node deleted, remove from keyList
      if(keyList[i] == deleteKey) {
	keyList.erase(keyList.begin() + i);
	cout << "Keylist pos: " << i << " deleted." << endl;
	return;
      }
    }
  }
  else { //Element found, elements in linkedlist
    cout << "Multiple students found with first name: " << deleteName << endl;
    cout << "Last name: ";
    char deleteLast[30];
    cin.getline(deleteLast, 30);
    Node* current = table[deleteKey];
    Node* prev = nullptr;
    while(::hash(current->getLast()) != ::hash(deleteLast)) { //Go through linkedlist until hashes match
      if(current == nullptr) {
	cout << "No student named: " << deleteName << " " << deleteLast << endl;
	return;
      }
      prev = current;
      current = current->getNext();
    }
    if(prev == nullptr) {
      table[deleteKey] = current->getNext();
    }
    else {
      prev->setNext(current->getNext());
    }
    delete current;
    cout << "Student deleted" << endl;
    for(int i = 0; i < keyList.size(); i++) { //If node deleted, remove from keyList
      if(keyList[i] == deleteKey) {
	keyList.erase(keyList.begin() + i);
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
void add(Node* newNode, Node* (&table)[], vector<int> &keyList, int tableSize) {
  int key = ::hash(newNode->getFirst()) % tableSize;
  keyList.push_back(key);
  if(table[key] == nullptr) {
    table[key] = newNode;
  }
  else {
    cout << "Collision, adding to linked list..." << endl;
    Node* top = table[key];
    newNode->setNext(top->getNext());
    top->setNext(newNode);
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
