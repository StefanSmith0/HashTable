#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

class Node {
 public:
  Node();
  ~Node();
  Node* getNext();
  void setNext(Node* newNext);
  char* getFirst();
  void setFirst(char* newFirst);
  char* getLast();
  void setLast(char* newLast);
  int getid();
  void setid(int newid);
  float getgpa();
  void setgpa(float newgpa);
 private:
  Node* nextNode;
  char firstName[30];
  char lastName[30];
  int id;
  float gpa;
};

#endif
