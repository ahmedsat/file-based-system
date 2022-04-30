#include <iostream>

#include <fstream>

#include "helperFileDBFunctions.cpp"

using namespace std;

string getDataByLine(string filename, int line)
{
  ifstream file(filename);

  file.close();
}

int main(int argc, char const *argv[])
{
  string a = getDataByLine("test.txt", 0);
  return 0;
}

// file-based-system