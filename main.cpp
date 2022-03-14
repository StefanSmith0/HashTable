/*
  Stefan Smith
  3/13/2022
  Hash Table

  Commands:
  add - Adds a student to the list.
  delete - Removes a student from the list.
  print - Prints list to console.
  quit - Ends the program and deletes the list.

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
void print(Node** table, vector<int> &keyList);
void add(Node* newNode, Node** table, vector<int> &keyList, int tableSize, int &collisions);
void deleteNode(char* deleteName, Node** table, vector<int> &keyList, int tableSize);
long hash(char *str);
float roundto2(float value);
void deleteTable(Node** table, vector<int> &keyList);
Node** rehash(Node** table, vector<int> &keyList, int newSize);

int main() {
  int tableSize = 51;
  Names* names = new Names();
  Node** table = new Node*[tableSize];
  for(int i = 0; i < tableSize; i++) {
    table[i] = nullptr;
  }
  vector<int> keyList;
  char input[30];
  bool running = true;
  int initialStudents = 5;
  int collisions = 0;
  cout << "Adding " << initialStudents << " random students to table." << endl;
  for(int i = 0; i < 12; i++) { //make random students
    add(newNode(i, names), table, keyList, tableSize, collisions);
    cout << collisions << " collisions" << endl;
  }
  while(running) {
    if(collisions >= 3) {
      cout << "More than three collisions, rehashing..." << endl;
      int newSize = ((tableSize - 1) * 2) + 1;
      table = rehash(table, keyList, newSize);
      tableSize = newSize;
      collisions = 0;
    }
    cout << "Command: ";
    cin.getline(input, 30);
    if(!strcmp(input, "quit")) {
      running = false;
    }
    else if(!strcmp(input, "delete")) {
      cout << "Student to delete: ";
      cin.getline(input, 30);
      deleteNode(input, table, keyList, tableSize);
    }
    else if(!strcmp(input, "print")) {
      print(table, keyList);
    }
    else if(!strcmp(input, "add")) {
      Node* newNode = new Node();
      int newid = 0;
      float newgpa = 0;
      cout << "First name: ";
      cin.getline(input, 30);
      newNode->setFirst(input);
      cout << "Last name: ";
      cin.getline(input, 30);
      newNode->setLast(input);
      cout << "ID: ";
      cin >> newid;
      newNode->setid(newid);
      cout << "GPA: ";
      cin >> newgpa;
      newNode->setgpa(newgpa);
      add(newNode, table, keyList, tableSize, collisions);
      cin.ignore(1000, '\n');
    }
  }
  deleteTable(table, keyList);
  delete names;
  return 0;
}

//Rehashes table into larger one.
Node** rehash(Node** table, vector<int> &keyList, int newSize) {
  Node* current;
  int newKey = 0;
  Node** newTable = new Node*[newSize];
  for(int i = 0; i < newSize; i++) { //Initializing new array
    newTable[i] = nullptr;
  }
  for(int i = 0; i < keyList.size(); i++) {
    current = table[keyList[i]];
    table[keyList[i]] = table[keyList[i]]->getNext();
    newKey = ::hash(current->getFirst()) % newSize;
    if(newTable[newKey] == nullptr) {
      current->setNext(nullptr);
      newTable[newKey] = current;
    }
    else {
      current->setNext(newTable[newKey]->getNext());
      newTable[newKey]->setNext(current);
    }
    keyList[i] = newKey;
  }
  cout << "Table resized to " << newSize << " students." << endl;
  return newTable;
}

//Deletes all Nodes in table.
void deleteTable(Node** table, vector<int> &keyList) {
  Node* current;
  for(int i = 0; i < keyList.size(); i++) {
    current = table[keyList[i]];
    if(current != nullptr) {
      if(current->getNext() == nullptr) {
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
	table[keyList[i]] = nullptr;
      }
    }
  }
}

//Delete a Node by name
void deleteNode(char* deleteName, Node** table, vector<int> &keyList, int tableSize) {
  int deleteKey = ::hash(deleteName) % tableSize;
  if(table[deleteKey] == nullptr) { //No element with input name
    cout << "Couldn't find student named: " << deleteName << endl;
  }
  else if(table[deleteKey]->getNext() == nullptr) { //Element found, no elements in linkedlist
    delete table[deleteKey];
    table[deleteKey] = nullptr;
    cout << "Student deleted." << endl;
    for(int i = 0; i < keyList.size(); i++) { //Node deleted, remove from keyList
      if(keyList[i] == deleteKey) {
	keyList.erase(keyList.begin() + i);
	return;
      }
    }
  }
  else { //Element found, elements in linkedlist
    cout << "Multiple candidates for name: " << deleteName << endl;
    cout << "Last name: ";
    char deleteLast[30];
    cin.getline(deleteLast, 30);
    Node* current = table[deleteKey];
    Node* prev = nullptr;
    while(::hash(current->getLast()) != ::hash(deleteLast)) { //Go through linkedlist until hashes match
      if(current == nullptr) {
	cout << "Couldn't find student named: " << deleteName << " " << deleteLast << endl;
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
    cout << "Student deleted." << endl;
    for(int i = 0; i < keyList.size(); i++) { //If node deleted, remove from keyList
      if(keyList[i] == deleteKey) {
	keyList.erase(keyList.begin() + i);
      }
    }
  }
}

//Prints table from keyList
void print(Node** table, vector<int> &keyList) {
  Node* current;
  Node* next;
  for(int i = 0; i < keyList.size(); i++) { //Print through hash table
    current = table[keyList[i]];
    next = current->getNext();
    cout << "Position: " << keyList[i] << endl;
    cout << "Student: " << current->getFirst() << " " << current->getLast() << endl;
    cout << "ID: " << current->getid() << endl;
    cout << "GPA: " << current->getgpa() << endl;
    while(next != nullptr) { //Print through linked list
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
void add(Node* newNode, Node** table, vector<int> &keyList, int tableSize, int &collisions) {
  int key = ::hash(newNode->getFirst()) % tableSize;
  keyList.push_back(key);
  if(table[key] == nullptr) {
    table[key] = newNode;
  }
  else {
    Node* top = table[key];
    newNode->setNext(top->getNext());
    top->setNext(newNode);
    collisions++;
  }
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
    hash = ((hash << 5) + hash) + c; // hash * 33 + c 
  }
  if(hash < 0) {
    hash = hash * -1;
  }
  return hash;
}

