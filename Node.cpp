#include "Node.h"
#include <cstring>

using namespace std;

Node::Node() {
  nextNode = NULL;
}

Node::~Node() {
  cout << "Node destroyed" << endl;
}

char* Node::getFirst() {
  return firstName;
}

void Node::setFirst(char* newFirst) {
  strcpy(firstName, newFirst);
}

char* Node::getLast() {
  return lastName;
}

void Node::setLast(char* newLast) {
  strcpy(lastName, newLast);
}

int Node::getid() {
  return id;
}

void Node::setid(int newid) {
  id = newid;
}

float Node::getgpa() {
  return gpa;
}

void Node::setgpa(float newgpa) {
  gpa = newgpa;
}

Node* Node::getNext() {
  return nextNode;
}

void Node::setNext(Node* newNext) {
  nextNode = newNext;
}
