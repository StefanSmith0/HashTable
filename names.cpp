#include "names.h"
#include <cstring>
#include <fstream>
#include <time.h>

Names::Names() {
  size = 101;
  srand(time(NULL));
  fstream firstNamesFile;
  firstNamesFile.open("firstNames.txt", ios::in);
  fillArray(size, firstNames, firstNamesFile);
  firstNamesFile.close();

  fstream lastNamesFile;
  lastNamesFile.open("lastNames.txt", ios::in);
  fillArray(size, lastNames, lastNamesFile);
  lastNamesFile.close();
}

Names::~Names() {
  cout << "Names deleted." << endl;
}

void Names::randFirst(char* input) {
  int randIndex = rand() % 100;
  strcpy(input, firstNames[randIndex].c_str());
}

void Names::randLast(char* input) {
  int randIndex = rand() % 100;
  strcpy(input, lastNames[randIndex].c_str());
}

void Names::fillArray(int size, string (&namesArray)[], fstream &file) {
  char* charArr[size];
  if(file.is_open()) {
    for(int i = 0; i < size; i++) {
      string newName;
      getline(file, newName);
      newName.pop_back();
      namesArray[i] = newName;
    }
  }
}
