#ifndef NAMES_H
#define NAMES_H
#include <iostream>
#include <string>


using namespace std;

class Names {
 public:
  Names();
  ~Names();
  void randFirst(char* input);
  void randLast(char* input);
 private:
  void fillArray(int size, string (&namesArray)[], fstream &file);
  int size;
  string firstNames[101];
  string lastNames[101];
};

#endif
